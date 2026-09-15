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
 *
 * The other half of the job is memory. Commands are small enough to travel in
 * GPR packets, but graphs, calibration blobs and audio data are passed by
 * address, and the DSP has to be able to reach that address - which means
 * memory mapped through the apps SMMU under the DSP's own stream id. The
 * AUDIO_PKT_IOCTL_ALLOC ioctl plus mmap() provide exactly that, allocated
 * against a child device carrying that stream id in its `iommus` property.
 * This mirrors what q6apm-dai does in-kernel for its PCM buffers, down to
 * putting the stream id in the top bits of the address handed to the DSP.
 */

#include <linux/dma-mapping.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/poll.h>
#include <linux/sched/signal.h>
#include <linux/slab.h>
#include <linux/soc/qcom/apr.h>
#include <linux/uaccess.h>
#include <linux/wait.h>

#include "audio_pkt.h"

/* GSL reads with a 4096 byte buffer; refuse anything that would not fit. */
#define AUDIO_PKT_MAX_SIZE	4096
/* GSL registers under a dozen ports. Bound it so a stray writer cannot
 * exhaust the router's idr. */
#define AUDIO_PKT_MAX_PORTS	32
/* Replies are small and consumed promptly; this is deep enough to absorb a
 * burst while the reader thread is scheduled out. */
#define AUDIO_PKT_MAX_QUEUE	64
/* q6apm-dai's SID_MASK_DEFAULT: only the low nibble of the stream id goes
 * into the address the DSP is given. */
#define AUDIO_PKT_SID_MASK	0xF
/* Enough for GSL's page bins several times over, and a bound on how much
 * coherent memory one open file can pin. */
#define AUDIO_PKT_MAX_BUFS	64
#define AUDIO_PKT_MAX_BUF_SIZE	(8 << 20)

struct audio_pkt_dev {
	struct apr_device *adev;
	struct miscdevice misc;
};

/*
 * The DMA device is the child node with the DSP's `iommus` stream id. It is a
 * plain platform device: the bus only runs of_dma_configure() when a driver
 * binds, so the trivial driver below exists purely to get the IOMMU domain set
 * up. There is one of these, so a single pointer is honest.
 */
static struct device *audio_pkt_dma_dev;
static u32 audio_pkt_sid;

struct audio_pkt_buf {
	struct list_head node;
	void *cpu;
	dma_addr_t dma;
	size_t size;
	u64 handle;
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

	/* DSP-visible buffers, freed with the file */
	struct mutex bufs_lock;
	struct list_head bufs;
	int nr_bufs;
	u64 next_handle;
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

/* Caller holds bufs_lock. */
static struct audio_pkt_buf *audio_pkt_find_buf(struct audio_pkt_file *apf,
						u64 handle)
{
	struct audio_pkt_buf *buf;

	list_for_each_entry(buf, &apf->bufs, node)
		if (buf->handle == handle)
			return buf;

	return NULL;
}

static void audio_pkt_free_buf(struct audio_pkt_buf *buf)
{
	dma_free_coherent(audio_pkt_dma_dev, buf->size, buf->cpu, buf->dma);
	kfree(buf);
}

static int audio_pkt_alloc(struct audio_pkt_file *apf,
			   struct audio_pkt_alloc __user *arg)
{
	struct audio_pkt_alloc req;
	struct audio_pkt_buf *buf;
	int ret = 0;

	if (!audio_pkt_dma_dev)
		return -ENODEV;

	if (copy_from_user(&req, arg, sizeof(req)))
		return -EFAULT;

	if (!req.size || req.size > AUDIO_PKT_MAX_BUF_SIZE)
		return -EINVAL;

	buf = kzalloc(sizeof(*buf), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	buf->size = PAGE_ALIGN(req.size);
	buf->cpu = dma_alloc_coherent(audio_pkt_dma_dev, buf->size, &buf->dma,
				      GFP_KERNEL);
	if (!buf->cpu) {
		kfree(buf);
		return -ENOMEM;
	}

	mutex_lock(&apf->bufs_lock);
	if (apf->nr_bufs >= AUDIO_PKT_MAX_BUFS) {
		ret = -ENOSPC;
		goto err;
	}

	/*
	 * The handle doubles as the mmap() offset, so it has to be page
	 * aligned and unique for the life of the file. A counter is both.
	 */
	buf->handle = apf->next_handle;
	apf->next_handle += buf->size;
	list_add_tail(&buf->node, &apf->bufs);
	apf->nr_bufs++;
	mutex_unlock(&apf->bufs_lock);

	req.size = buf->size;
	req.handle = buf->handle;
	req.dsp_addr = buf->dma | ((u64)audio_pkt_sid << 32);

	if (copy_to_user(arg, &req, sizeof(req))) {
		mutex_lock(&apf->bufs_lock);
		list_del(&buf->node);
		apf->nr_bufs--;
		mutex_unlock(&apf->bufs_lock);
		audio_pkt_free_buf(buf);
		return -EFAULT;
	}

	return 0;
err:
	mutex_unlock(&apf->bufs_lock);
	audio_pkt_free_buf(buf);
	return ret;
}

static int audio_pkt_free(struct audio_pkt_file *apf, u64 __user *arg)
{
	struct audio_pkt_buf *buf;
	u64 handle;

	if (copy_from_user(&handle, arg, sizeof(handle)))
		return -EFAULT;

	mutex_lock(&apf->bufs_lock);
	buf = audio_pkt_find_buf(apf, handle);
	if (buf) {
		list_del(&buf->node);
		apf->nr_bufs--;
	}
	mutex_unlock(&apf->bufs_lock);

	if (!buf)
		return -ENOENT;

	audio_pkt_free_buf(buf);

	return 0;
}

static long audio_pkt_ioctl(struct file *file, unsigned int cmd,
			    unsigned long arg)
{
	struct audio_pkt_file *apf = file->private_data;

	switch (cmd) {
	case AUDIO_PKT_IOCTL_ALLOC:
		return audio_pkt_alloc(apf, (struct audio_pkt_alloc __user *)arg);
	case AUDIO_PKT_IOCTL_FREE:
		return audio_pkt_free(apf, (u64 __user *)arg);
	default:
		return -ENOTTY;
	}
}

static int audio_pkt_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct audio_pkt_file *apf = file->private_data;
	unsigned long size = vma->vm_end - vma->vm_start;
	struct audio_pkt_buf *buf;
	int ret;

	if (!audio_pkt_dma_dev)
		return -ENODEV;

	mutex_lock(&apf->bufs_lock);
	buf = audio_pkt_find_buf(apf, (u64)vma->vm_pgoff << PAGE_SHIFT);
	if (!buf || size > buf->size) {
		mutex_unlock(&apf->bufs_lock);
		return -EINVAL;
	}

	/*
	 * dma_mmap_coherent() reads vm_pgoff as an offset within the buffer,
	 * not as the lookup key it was on the way in. Clear it, or it maps
	 * past the end of the allocation.
	 */
	vma->vm_pgoff = 0;
	ret = dma_mmap_coherent(audio_pkt_dma_dev, vma, buf->cpu, buf->dma,
				buf->size);
	mutex_unlock(&apf->bufs_lock);

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
	mutex_init(&apf->bufs_lock);
	INIT_LIST_HEAD(&apf->bufs);

	file->private_data = apf;
	stream_open(inode, file);

	return 0;
}

static int audio_pkt_release(struct inode *inode, struct file *file)
{
	struct audio_pkt_file *apf = file->private_data;
	struct audio_pkt_port *apport, *pn;
	struct audio_pkt_buf *buf, *bn;
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

	/*
	 * Safe to free the coherent allocations here: an mmap holds a
	 * reference to the file through vma->vm_file, so release() cannot run
	 * while any mapping of these buffers is still alive.
	 */
	mutex_lock(&apf->bufs_lock);
	list_for_each_entry_safe(buf, bn, &apf->bufs, node) {
		list_del(&buf->node);
		audio_pkt_free_buf(buf);
	}
	mutex_unlock(&apf->bufs_lock);

	mutex_destroy(&apf->bufs_lock);
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
	.unlocked_ioctl	= audio_pkt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.mmap		= audio_pkt_mmap,
};

/*
 * The DMA child. It claims no registers and does nothing; binding a driver to
 * it is what makes the bus run of_dma_configure() and put it in the SMMU
 * domain named by its `iommus` property - the DSP's. Allocations made against
 * this device are therefore addressable by the DSP.
 */
static int audio_pkt_dma_probe(struct platform_device *pdev)
{
	struct of_phandle_args args;
	int ret;

	ret = of_parse_phandle_with_fixed_args(pdev->dev.of_node, "iommus", 1,
					       0, &args);
	if (ret < 0) {
		dev_err(&pdev->dev, "no iommus property, the DSP could not reach these buffers\n");
		return ret;
	}
	of_node_put(args.np);

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	audio_pkt_sid = args.args[0] & AUDIO_PKT_SID_MASK;
	audio_pkt_dma_dev = &pdev->dev;
	dev_info(&pdev->dev, "DSP buffer allocator ready, sid %u\n",
		 audio_pkt_sid);

	return 0;
}

static void audio_pkt_dma_remove(struct platform_device *pdev)
{
	audio_pkt_dma_dev = NULL;
}

static const struct of_device_id audio_pkt_dma_of_match[] = {
	{ .compatible = "qcom,audio-pkt-mem" },
	{}
};
MODULE_DEVICE_TABLE(of, audio_pkt_dma_of_match);

static struct platform_driver audio_pkt_dma_driver = {
	.probe	= audio_pkt_dma_probe,
	.remove	= audio_pkt_dma_remove,
	.driver	= {
		.name = "qcom-audio-pkt-mem",
		.of_match_table = audio_pkt_dma_of_match,
	},
};

static int audio_pkt_probe(struct apr_device *adev)
{
	struct device *dev = &adev->dev;
	struct audio_pkt_dev *apdev;
	int ret;

	apdev = devm_kzalloc(dev, sizeof(*apdev), GFP_KERNEL);
	if (!apdev)
		return -ENOMEM;

	apdev->adev = adev;
	apdev->misc.minor = MISC_DYNAMIC_MINOR;
	apdev->misc.name = "aud_pasthru_adsp";
	apdev->misc.fops = &audio_pkt_fops;
	apdev->misc.parent = dev;

	dev_set_drvdata(dev, apdev);

	/* brings up the "memory" child, and with it the DSP buffer allocator */
	ret = devm_of_platform_populate(dev);
	if (ret)
		dev_warn(dev, "no DMA child: packets will work, buffers will not (%d)\n",
			 ret);

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

/*
 * Two drivers, so no module_apr_driver() shorthand: the DMA child's driver has
 * to be registered before the GPR device probes and populates it, or the child
 * device sits unbound and never gets its IOMMU domain.
 */
static int __init audio_pkt_init(void)
{
	int ret;

	ret = platform_driver_register(&audio_pkt_dma_driver);
	if (ret)
		return ret;

	ret = apr_driver_register(&audio_pkt_driver);
	if (ret)
		platform_driver_unregister(&audio_pkt_dma_driver);

	return ret;
}
module_init(audio_pkt_init);

static void __exit audio_pkt_exit(void)
{
	apr_driver_unregister(&audio_pkt_driver);
	platform_driver_unregister(&audio_pkt_dma_driver);
}
module_exit(audio_pkt_exit);

MODULE_DESCRIPTION("Qualcomm GPR passthrough character device");
MODULE_LICENSE("GPL");
