// SPDX-License-Identifier: GPL-2.0
/*
 * Raw GPR passthrough character device for the ADSP.
 *
 * Qualcomm's AudioReach userspace (GSL, in audioreach-graphservices) talks to
 * the ADSP's signal processing framework over exactly one file:
 *
 *	gpr/datalinks/gpr_lx/src/gpr_lx.c:
 *	  #define GPR_DL_LX_ADSP_DRV "/dev/aud_pasthru_adsp"
 *	  fd = open(drv, O_RDWR);  read(fd, buf, 4096);  write(fd, buf, size);
 *	  poll(pfd, 2, -1);
 *
 * One whole GPR packet per read and per write, no extra framing. This driver
 * is that file, and nothing else - it does not interpret the packets.
 *
 * Mainline's packet router (drivers/soc/qcom/apr.c) already does the two hard
 * parts: pkt_router_send_svc_pkt() hands the packet to rpmsg verbatim without
 * rewriting the header, and gpr_do_rx_callback() routes replies by looking up
 * hdr->dest_port in the router's idr. So the only thing missing is a port
 * registered at the id userspace chose: the ADSP echoes a command's src_port
 * back as the reply's dest_port, and an unregistered one is dropped with
 * "GPR: Port(%x) is not registered". GSL picks its own ids (0x2002..0x3003,
 * see GSL_MAIN_SRC_PORT and friends), which is why gpr_alloc_port_id() exists.
 *
 * Ports are therefore created lazily: the first packet written from a given
 * src_port registers that port, and it lives until the file is closed.
 */

#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/poll.h>
#include <linux/sched/signal.h>
#include <linux/slab.h>
#include <linux/soc/qcom/apr.h>
#include <linux/uaccess.h>
#include <linux/wait.h>

/* GSL reads with a 4096 byte buffer; refuse anything that would not fit. */
#define AUDIO_PKT_MAX_SIZE	4096
/* GSL registers under a dozen ports. Bound it so a stray writer cannot
 * exhaust the router's idr. */
#define AUDIO_PKT_MAX_PORTS	32
/* Replies are small and consumed promptly; this is deep enough to absorb a
 * burst while the reader thread is scheduled out. */
#define AUDIO_PKT_MAX_QUEUE	64

struct audio_pkt_dev {
	struct apr_device *adev;
	struct miscdevice misc;
};

struct audio_pkt_rx {
	struct list_head node;
	int len;
	u8 buf[] __counted_by(len);
};

struct audio_pkt_port {
	struct list_head node;
	u32 id;
	gpr_port_t *port;
	struct audio_pkt_file *apf;
};

struct audio_pkt_file {
	struct audio_pkt_dev *apdev;

	/* ports: created from write(), torn down from release() */
	struct mutex ports_lock;
	struct list_head ports;
	int nr_ports;

	/* rx queue: filled from the router's rx workqueue, drained by read() */
	spinlock_t queue_lock;
	struct list_head queue;
	int nr_queued;
	wait_queue_head_t readq;
};

static int audio_pkt_callback(struct gpr_resp_pkt *resp, void *priv, int op)
{
	struct audio_pkt_port *apport = priv;
	struct audio_pkt_file *apf = apport->apf;
	struct audio_pkt_rx *rx;
	struct gpr_hdr *hdr;
	int payload, len;
	unsigned long flags;

	payload = resp->payload_size > 0 ? resp->payload_size : 0;
	len = sizeof(*hdr) + payload;
	if (len > AUDIO_PKT_MAX_SIZE)
		return -EMSGSIZE;

	rx = kzalloc(struct_size(rx, buf, len), GFP_ATOMIC);
	if (!rx)
		return -ENOMEM;

	/*
	 * The router hands over a copy of the header plus a pointer into its
	 * own buffer. Reassemble one contiguous packet, and state the size we
	 * actually produced: the remote may have included optional headers
	 * that gpr_do_rx_callback() already skipped past.
	 */
	rx->len = len;
	hdr = (struct gpr_hdr *)rx->buf;
	*hdr = resp->hdr;
	hdr->hdr_size = sizeof(*hdr) / sizeof(u32);
	hdr->pkt_size = len;
	if (payload)
		memcpy(rx->buf + sizeof(*hdr), resp->payload, payload);

	spin_lock_irqsave(&apf->queue_lock, flags);
	if (apf->nr_queued >= AUDIO_PKT_MAX_QUEUE) {
		spin_unlock_irqrestore(&apf->queue_lock, flags);
		kfree(rx);
		return -ENOBUFS;
	}
	list_add_tail(&rx->node, &apf->queue);
	apf->nr_queued++;
	spin_unlock_irqrestore(&apf->queue_lock, flags);

	wake_up_interruptible(&apf->readq);

	return 0;
}

/* Caller holds ports_lock. */
static struct audio_pkt_port *audio_pkt_get_port(struct audio_pkt_file *apf,
						 u32 id)
{
	struct audio_pkt_dev *apdev = apf->apdev;
	struct audio_pkt_port *apport;

	list_for_each_entry(apport, &apf->ports, node)
		if (apport->id == id)
			return apport;

	if (apf->nr_ports >= AUDIO_PKT_MAX_PORTS)
		return ERR_PTR(-ENOSPC);

	apport = kzalloc(sizeof(*apport), GFP_KERNEL);
	if (!apport)
		return ERR_PTR(-ENOMEM);

	apport->id = id;
	apport->apf = apf;
	apport->port = gpr_alloc_port_id(apdev->adev, apdev->misc.this_device,
					 audio_pkt_callback, apport, id);
	if (IS_ERR(apport->port)) {
		void *err = apport->port;

		kfree(apport);
		return err;
	}

	list_add_tail(&apport->node, &apf->ports);
	apf->nr_ports++;

	return apport;
}

static ssize_t audio_pkt_write(struct file *file, const char __user *ubuf,
			       size_t count, loff_t *ppos)
{
	struct audio_pkt_file *apf = file->private_data;
	struct audio_pkt_port *apport;
	struct gpr_pkt *pkt;
	int ret;

	if (count < sizeof(struct gpr_hdr) || count > AUDIO_PKT_MAX_SIZE)
		return -EINVAL;

	pkt = memdup_user(ubuf, count);
	if (IS_ERR(pkt))
		return PTR_ERR(pkt);

	/* rpmsg_trysend() sends hdr.pkt_size bytes; do not let it read past
	 * what userspace actually handed over. */
	if (pkt->hdr.pkt_size != count) {
		ret = -EINVAL;
		goto out;
	}

	mutex_lock(&apf->ports_lock);
	apport = audio_pkt_get_port(apf, pkt->hdr.src_port);
	mutex_unlock(&apf->ports_lock);
	if (IS_ERR(apport)) {
		ret = PTR_ERR(apport);
		goto out;
	}

	ret = gpr_send_port_pkt(apport->port, pkt);
	if (ret >= 0)
		ret = count;
out:
	kfree(pkt);
	return ret;
}

static ssize_t audio_pkt_read(struct file *file, char __user *ubuf,
			      size_t count, loff_t *ppos)
{
	struct audio_pkt_file *apf = file->private_data;
	struct audio_pkt_rx *rx;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&apf->queue_lock, flags);
	while (list_empty(&apf->queue)) {
		spin_unlock_irqrestore(&apf->queue_lock, flags);

		if (file->f_flags & O_NONBLOCK)
			return -EAGAIN;

		ret = wait_event_interruptible(apf->readq,
					       !list_empty(&apf->queue));
		if (ret)
			return ret;

		spin_lock_irqsave(&apf->queue_lock, flags);
	}
	rx = list_first_entry(&apf->queue, struct audio_pkt_rx, node);

	/* A GPR packet is only meaningful whole. Leave it queued rather than
	 * hand back a truncated one. */
	if (rx->len > count) {
		spin_unlock_irqrestore(&apf->queue_lock, flags);
		return -EMSGSIZE;
	}

	list_del(&rx->node);
	apf->nr_queued--;
	spin_unlock_irqrestore(&apf->queue_lock, flags);

	ret = copy_to_user(ubuf, rx->buf, rx->len) ? -EFAULT : rx->len;
	kfree(rx);

	return ret;
}

static __poll_t audio_pkt_poll(struct file *file, poll_table *wait)
{
	struct audio_pkt_file *apf = file->private_data;
	__poll_t mask = EPOLLOUT | EPOLLWRNORM;
	unsigned long flags;

	poll_wait(file, &apf->readq, wait);

	spin_lock_irqsave(&apf->queue_lock, flags);
	if (!list_empty(&apf->queue))
		mask |= EPOLLIN | EPOLLRDNORM;
	spin_unlock_irqrestore(&apf->queue_lock, flags);

	return mask;
}

static int audio_pkt_open(struct inode *inode, struct file *file)
{
	struct audio_pkt_dev *apdev =
		container_of(file->private_data, struct audio_pkt_dev, misc);
	struct audio_pkt_file *apf;

	apf = kzalloc(sizeof(*apf), GFP_KERNEL);
	if (!apf)
		return -ENOMEM;

	apf->apdev = apdev;
	mutex_init(&apf->ports_lock);
	INIT_LIST_HEAD(&apf->ports);
	spin_lock_init(&apf->queue_lock);
	INIT_LIST_HEAD(&apf->queue);
	init_waitqueue_head(&apf->readq);

	file->private_data = apf;
	stream_open(inode, file);

	return 0;
}

static int audio_pkt_release(struct inode *inode, struct file *file)
{
	struct audio_pkt_file *apf = file->private_data;
	struct audio_pkt_port *apport, *pn;
	struct audio_pkt_rx *rx, *rn;
	unsigned long flags;

	/* Unregister the ports first: once they are gone no further packet can
	 * be queued, so the drain below is final. */
	mutex_lock(&apf->ports_lock);
	list_for_each_entry_safe(apport, pn, &apf->ports, node) {
		list_del(&apport->node);
		gpr_free_port(apport->port);
		kfree(apport);
	}
	mutex_unlock(&apf->ports_lock);

	spin_lock_irqsave(&apf->queue_lock, flags);
	list_for_each_entry_safe(rx, rn, &apf->queue, node) {
		list_del(&rx->node);
		kfree(rx);
	}
	spin_unlock_irqrestore(&apf->queue_lock, flags);

	mutex_destroy(&apf->ports_lock);
	kfree(apf);

	return 0;
}

static const struct file_operations audio_pkt_fops = {
	.owner		= THIS_MODULE,
	.open		= audio_pkt_open,
	.release	= audio_pkt_release,
	.read		= audio_pkt_read,
	.write		= audio_pkt_write,
	.poll		= audio_pkt_poll,
};

static int audio_pkt_probe(struct apr_device *adev)
{
	struct device *dev = &adev->dev;
	struct audio_pkt_dev *apdev;

	apdev = devm_kzalloc(dev, sizeof(*apdev), GFP_KERNEL);
	if (!apdev)
		return -ENOMEM;

	apdev->adev = adev;
	apdev->misc.minor = MISC_DYNAMIC_MINOR;
	apdev->misc.name = "aud_pasthru_adsp";
	apdev->misc.fops = &audio_pkt_fops;
	apdev->misc.parent = dev;

	dev_set_drvdata(dev, apdev);

	return misc_register(&apdev->misc);
}

static void audio_pkt_remove(struct apr_device *adev)
{
	struct audio_pkt_dev *apdev = dev_get_drvdata(&adev->dev);

	misc_deregister(&apdev->misc);
}

static const struct of_device_id audio_pkt_device_id[] = {
	{ .compatible = "qcom,audio-pkt" },
	{}
};
MODULE_DEVICE_TABLE(of, audio_pkt_device_id);

static struct apr_driver audio_pkt_driver = {
	.probe	= audio_pkt_probe,
	.remove	= audio_pkt_remove,
	.driver	= {
		.name = "qcom-audio-pkt",
		.of_match_table = audio_pkt_device_id,
	},
};

module_apr_driver(audio_pkt_driver);

MODULE_DESCRIPTION("Qualcomm GPR passthrough character device");
MODULE_LICENSE("GPL");
