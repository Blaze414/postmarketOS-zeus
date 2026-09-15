/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * ar_osal shared memory backed by /dev/aud_pasthru_adsp.
 *
 * Replaces ar_osal_shmem_virtual.c, which hands the DSP a malloc'd page it
 * cannot reach - the DSP answers APM_CMD_SHARED_MEM_MAP_REGIONS with a plain
 * error and GSL gives up during init. Here the kernel allocates coherent
 * memory against a device carrying the DSP's SMMU stream id and returns the
 * address the DSP should be given, which is what goes into the map command.
 *
 * Both graphservices' own Linux backends were unusable as-is: the ION one
 * (ar_osal_shmem_ion.c) needs Android's ION, and the dma-heap one
 * (ar_osal_shmem_db.c) needs downstream's linux/msm_audio.h for the ioctl
 * that performs the DSP-side mapping. The ioctl here is that missing piece.
 *
 * On what GSL does with these fields: gsl_shmem_map_page_to_spf() puts
 * ipa_lsw/ipa_msw straight into the map command, and derives its property
 * flags from index_type and mem_type. Reporting a real address in address
 * mode (not offset mode) also means client_data stays zero, so the kernel is
 * not asked to substitute a physical address the way the Android stack does -
 * we already have the right one.
 */
#define AR_OSAL_SHMEM_LOG_TAG "APSH"

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "ar_osal_error.h"
#include "ar_osal_log.h"
#include "ar_osal_shmem.h"
#include "ar_osal_sys_id.h"

#include "audio_pkt.h"

#define AUDIO_PKT_DEV	"/dev/aud_pasthru_adsp"
#define SHMEM_4K	4096

/* One fd for every allocation: buffers belong to the open file, and GSL's
 * transport fd is opened and closed independently of this. */
static int shmem_fd = -1;

/* Kept per allocation so free() can unmap and hand the handle back. */
struct shmem_meta {
	uint64_t handle;
	size_t size;
	void *vaddr;
};

int32_t ar_shmem_validate_sys_id(uint8_t num_sys_id, ar_shmem_proc_info *sys_id)
{
	if (!num_sys_id || !sys_id)
		return AR_EBADPARAM;

	for (uint8_t i = 0; i < num_sys_id; i++) {
		switch (sys_id[i].proc_id) {
		case AR_AUDIO_DSP:
		case AR_MODEM_DSP:
		case AR_SENSOR_DSP:
		case AR_COMPUTE_DSP:
		case AR_APSS:
		case AR_APSS2:
			break;
		default:
			return AR_EBADPARAM;
		}
	}

	return AR_EOK;
}

int32_t ar_shmem_init(void)
{
	if (shmem_fd >= 0)
		return AR_EOK;

	shmem_fd = open(AUDIO_PKT_DEV, O_RDWR);
	if (shmem_fd < 0) {
		AR_LOG_ERR(AR_OSAL_SHMEM_LOG_TAG, "open %s failed: %d",
			   AUDIO_PKT_DEV, errno);
		return AR_ENOTEXIST;
	}

	return AR_EOK;
}

int32_t ar_shmem_init_v2(uint32_t num_master_procs, uint32_t *master_procs)
{
	(void)num_master_procs;
	(void)master_procs;
	return ar_shmem_init();
}

int32_t ar_shmem_deinit(void)
{
	if (shmem_fd >= 0) {
		close(shmem_fd);
		shmem_fd = -1;
	}

	return AR_EOK;
}

int32_t ar_shmem_alloc(ar_shmem_info *info)
{
	struct audio_pkt_alloc req = { 0 };
	struct shmem_meta *meta;
	void *p;

	if (!info || !info->buf_size)
		return AR_EBADPARAM;

	if (AR_EOK != ar_shmem_validate_sys_id(info->num_sys_id, info->sys_id))
		return AR_EBADPARAM;

	if (shmem_fd < 0 && AR_EOK != ar_shmem_init())
		return AR_ENOTEXIST;

	meta = calloc(1, sizeof(*meta));
	if (!meta)
		return AR_ENOMEMORY;

	req.size = info->buf_size;
	if (ioctl(shmem_fd, AUDIO_PKT_IOCTL_ALLOC, &req) < 0) {
		AR_LOG_ERR(AR_OSAL_SHMEM_LOG_TAG, "ALLOC of %zu failed: %d",
			   info->buf_size, errno);
		free(meta);
		return AR_ENOMEMORY;
	}

	/* The handle is the mmap offset; the kernel picked it page aligned. */
	p = mmap(NULL, req.size, PROT_READ | PROT_WRITE, MAP_SHARED, shmem_fd,
		 (off_t)req.handle);
	if (p == MAP_FAILED) {
		AR_LOG_ERR(AR_OSAL_SHMEM_LOG_TAG, "mmap failed: %d", errno);
		ioctl(shmem_fd, AUDIO_PKT_IOCTL_FREE, &req.handle);
		free(meta);
		return AR_ENOMEMORY;
	}

	if ((uintptr_t)p % SHMEM_4K) {
		AR_LOG_ERR(AR_OSAL_SHMEM_LOG_TAG, "vaddr %p not 4K aligned", p);
		munmap(p, req.size);
		ioctl(shmem_fd, AUDIO_PKT_IOCTL_FREE, &req.handle);
		free(meta);
		return AR_EUNEXPECTED;
	}

	meta->handle = req.handle;
	meta->size = req.size;
	meta->vaddr = p;

	info->vaddr = p;
	info->metadata = (uint64_t)(uintptr_t)meta;
	info->mem_type = AR_SHMEM_PHYSICAL_MEMORY;
	info->index_type = AR_SHMEM_BUFFER_ADDRESS;
	info->ipa_lsw = info->pa_lsw = (uint32_t)req.dsp_addr;
	info->ipa_msw = info->pa_msw = (uint32_t)(req.dsp_addr >> 32);

	AR_LOG_DEBUG(AR_OSAL_SHMEM_LOG_TAG,
		     "alloc %zu vaddr %p dsp 0x%08x%08x", meta->size, p,
		     info->ipa_msw, info->ipa_lsw);

	return AR_EOK;
}

int32_t ar_shmem_free(ar_shmem_info *info)
{
	struct shmem_meta *meta;

	if (!info || !info->metadata)
		return AR_EBADPARAM;

	if (AR_EOK != ar_shmem_validate_sys_id(info->num_sys_id, info->sys_id))
		return AR_EBADPARAM;

	meta = (struct shmem_meta *)(uintptr_t)info->metadata;
	munmap(meta->vaddr, meta->size);
	if (shmem_fd >= 0)
		ioctl(shmem_fd, AUDIO_PKT_IOCTL_FREE, &meta->handle);
	free(meta);

	info->metadata = 0;
	info->vaddr = NULL;

	return AR_EOK;
}

/*
 * map/unmap exist for memory the client allocated itself and wants the DSP to
 * reach. Nothing on this path does that - GSL allocates through alloc() above
 * - and honouring it would mean importing a dma-buf, which the ioctl does not
 * offer yet. Refuse rather than hand back an address the DSP cannot use.
 */
int32_t ar_shmem_map(ar_shmem_info *info)
{
	(void)info;
	AR_LOG_ERR(AR_OSAL_SHMEM_LOG_TAG,
		   "mapping client-allocated memory is not supported");
	return AR_EUNSUPPORTED;
}

int32_t ar_shmem_unmap(ar_shmem_info *info)
{
	(void)info;
	return AR_EOK;
}

/* No hypervisor memory assignment on this platform. */
int32_t ar_shmem_hyp_assign_phys(ar_shmem_hyp_assign_phys_info *info)
{
	(void)info;
	return AR_EOK;
}

int32_t ar_shmem_get_uid(uint64_t alloc_handle, uint64_t *uid)
{
	if (!uid)
		return AR_EFAILED;

	*uid = alloc_handle;

	return AR_EOK;
}
