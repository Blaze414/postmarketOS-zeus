/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Userspace interface of the GPR passthrough character device.
 *
 * Packets go over plain read()/write(). These ioctls exist for the other half
 * of the job: buffers the audio DSP can read. Userspace asks for one, mmaps it
 * at the returned handle, and hands the returned address to the DSP in
 * APM_CMD_SHARED_MEM_MAP_REGIONS.
 */
#ifndef _UAPI_LINUX_AUDIO_PKT_H
#define _UAPI_LINUX_AUDIO_PKT_H

#include <linux/ioctl.h>
#include <linux/types.h>

struct audio_pkt_alloc {
	/** in: bytes, rounded up to a page */
	__u64 size;
	/** out: pass as the mmap() offset, and to FREE */
	__u64 handle;
	/**
	 * out: the address to give the DSP. This is the buffer's address in
	 * the DSP's own address space - its SMMU stream id in the top bits,
	 * the mapped address below - not a physical address, and of no use to
	 * userspace for anything but filling in a memory-map command.
	 */
	__u64 dsp_addr;
};

#define AUDIO_PKT_IOCTL_MAGIC		'q'
#define AUDIO_PKT_IOCTL_ALLOC		_IOWR(AUDIO_PKT_IOCTL_MAGIC, 1, struct audio_pkt_alloc)
#define AUDIO_PKT_IOCTL_FREE		_IOW(AUDIO_PKT_IOCTL_MAGIC, 2, __u64)

#endif /* _UAPI_LINUX_AUDIO_PKT_H */
