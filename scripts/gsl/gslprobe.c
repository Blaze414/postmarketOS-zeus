/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Bring GSL up against the real DSP, control path only.
 *
 * gsl_init() loads the calibration database, registers its GPR ports and then
 * polls Spf for readiness - which is the first thing on this port that has to
 * cross /dev/aud_pasthru_adsp and come back. If that returns, the passthrough
 * and GSL's own transport agree, and the premise of the userspace port holds.
 *
 *   gslprobe /abs/path/Mise_elus_acdb_cal.acdb [key=value ...]
 *
 * Given a graph key vector it goes further and opens that graph, then prepares
 * and starts it. The speaker playback path on this device is
 *
 *   gslprobe .../Mise_elus_acdb_cal.acdb a1000000=a1000003 a2000000=a2000001
 *
 * which is the question the whole exercise exists to answer: whether the DSP
 * will configure a TDM sink for a graph opened this way, when it will not for
 * the same endpoint driven by the in-kernel q6apm (doc 11).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "gsl_intf.h"
#include "gsl_hw_rsc_intf.h"
#include "prm_api.h"
#include "hw_core_api.h"
#include "media_fmt_api_basic.h"
#include <stddef.h>

void ar_log_init(void);

#define MAX_KVPS	16
/* 48 kHz, stereo, 16-bit: 10 ms of audio. */
#define PERIOD_BYTES	1920
#define PERIODS		100
/*
 * The tag naming a stream's shared-memory write endpoint. Not defined in
 * graphservices - it comes from the tag list Qualcomm's own clients compile
 * in - but it is stable across AudioReach releases.
 */
#define SHMEM_ENDPOINT	0xC0000001

/*
 * Vote the LPASS hardware core on, through the DSP's proxy resource manager.
 *
 * Nothing else does it on this system. In the Android stack the client (AGM)
 * makes this request itself before starting a graph; under mainline the
 * kernel's q6prm does the equivalent when ASoC brings a path up, but a graph
 * opened straight from userspace goes through neither. A hardware endpoint
 * cannot start with its core unpowered, which fits what is seen: every graph
 * opens and prepares, and every graph fails to start.
 *
 * gsl_request_hw_rsc_custom_config() takes {miid, pid, size, error_code}
 * followed by the parameter payload.
 */
static int32_t vote_lpass_core(void)
{
	struct {
		uint32_t miid;
		uint32_t pid;
		uint32_t size;
		uint32_t error_code;
		struct hw_core_request_t req;
	} p;
	int32_t rc;

	memset(&p, 0, sizeof(p));
	p.miid = PRM_MODULE_INSTANCE_ID;
	p.pid = PARAM_ID_RSC_HW_CORE;
	p.size = sizeof(p.req);
	p.req.hw_core_id = HW_CORE_ID_LPASS;

	rc = gsl_request_hw_rsc_custom_config((const uint8_t *)&p, sizeof(p),
					      NULL, NULL);
	printf("LPASS core vote: %d (%s)\n", rc, rc ? "FAILED" : "OK");

	return rc;
}

/*
 * Tell the stream's write endpoint what the data looks like.
 *
 * A container cannot start a module whose input media format is unknown, so a
 * graph with no format set refuses GRAPH_START - which matches what is seen
 * here: every graph opens and prepares and none of them starts, whether or not
 * it even has a hardware endpoint. The in-kernel path does the same thing in
 * q6apm_graph_media_format_pcm() before it prepares or starts.
 *
 * The payload is SPF's out-of-band form, {miid, pid, size, error_code}
 * followed by the parameter.
 */
static int32_t set_media_format(gsl_handle_t graph,
				const struct gsl_key_vector *gkv)
{
	struct gsl_module_id_info *info = NULL;
	uint32_t info_size = 0;
	int32_t rc;
	struct {
		uint32_t miid;
		uint32_t pid;
		uint32_t size;
		uint32_t error_code;
		media_format_t fmt;
		payload_media_fmt_pcm_t pcm;
		uint8_t channel_map[2];
	} p;

	rc = gsl_get_tagged_module_info(gkv, SHMEM_ENDPOINT, &info, &info_size);
	if (rc || !info || !info->num_modules) {
		printf("no module tagged SHMEM_ENDPOINT: %d\n", rc);
		return rc ? rc : -1;
	}

	memset(&p, 0, sizeof(p));
	p.miid = info->module_entry[0].module_iid;
	p.pid = PARAM_ID_MEDIA_FORMAT;
	p.size = sizeof(p) - offsetof(typeof(p), fmt);
	p.fmt.data_format = DATA_FORMAT_FIXED_POINT;
	p.fmt.fmt_id = MEDIA_FMT_ID_PCM;
	p.fmt.payload_size = sizeof(p.pcm) + sizeof(p.channel_map);
	p.pcm.sample_rate = 48000;
	p.pcm.bit_width = 16;
	p.pcm.alignment = PCM_LSB_ALIGNED;
	p.pcm.interleaved = PCM_INTERLEAVED;
	p.pcm.bits_per_sample = 16;
	p.pcm.q_factor = 15;
	p.pcm.endianness = PCM_LITTLE_ENDIAN;
	p.pcm.num_channels = 2;
	p.channel_map[0] = 1;	/* front left */
	p.channel_map[1] = 2;	/* front right */

	printf("media format -> miid 0x%x (48k/16/2)\n", p.miid);
	rc = gsl_set_custom_config(graph, (const uint8_t *)&p, sizeof(p));
	printf("gsl_set_custom_config MEDIA_FORMAT: %d (%s)\n", rc,
	       rc ? "FAILED" : "OK");

	free(info);

	return rc;
}

static void play_tone(gsl_handle_t graph)
{
	static int16_t frame[PERIOD_BYTES / 2];
	struct gsl_buff buff;
	uint32_t consumed;
	int32_t rc = 0;

	/* ~440 Hz square wave: audible, and trivial to generate. */
	for (unsigned i = 0; i < PERIOD_BYTES / 2; i += 2) {
		int16_t v = ((i / 2) / 54) % 2 ? 8000 : -8000;

		frame[i] = frame[i + 1] = v;
	}

	printf("writing %d periods (%d ms)\n", PERIODS, PERIODS * 10);
	for (int n = 0; n < PERIODS && !rc; n++) {
		memset(&buff, 0, sizeof(buff));
		buff.size = sizeof(frame);
		buff.addr = (uint8_t *)frame;
		consumed = 0;
		rc = gsl_write(graph, SHMEM_ENDPOINT, &buff, &consumed);
		if (rc)
			printf("gsl_write failed at period %d: %d\n", n, rc);
	}
	if (!rc)
		printf("wrote all periods OK\n");

	gsl_ioctl(graph, GSL_CMD_STOP, NULL, 0);
}

static int32_t open_graph(int nkv, char **kvargs)
{
	struct gsl_cmd_configure_read_write_params wr;
	struct gsl_key_value_pair kvp[MAX_KVPS];
	struct gsl_key_vector gkv;
	gsl_handle_t graph = NULL;
	int32_t rc;

	if (nkv > MAX_KVPS)
		nkv = MAX_KVPS;

	for (int i = 0; i < nkv; i++) {
		if (sscanf(kvargs[i], "%x=%x", &kvp[i].key, &kvp[i].value) != 2) {
			fprintf(stderr, "bad key=value: %s\n", kvargs[i]);
			return -1;
		}
		printf("  gkv[%d] %08x=%08x\n", i, kvp[i].key, kvp[i].value);
	}

	gkv.num_kvps = nkv;
	gkv.kvp = kvp;

	vote_lpass_core();

	/* No calibration key vector: the graph's own defaults are enough to
	 * see whether the endpoint gets configured at all. */
	rc = gsl_open(&gkv, NULL, &graph);
	printf("gsl_open: %d (%s)\n", rc, rc ? "FAILED" : "OK");
	if (rc)
		return rc;

	/*
	 * Configure the write path before starting. A playback graph's shared
	 * memory endpoint has no buffers until this is done, and GSL also uses
	 * it to decide when to issue START to the DSP - which is why a graph
	 * that opens and prepares cleanly can still refuse to start.
	 * start_threshold 0 asks for an immediate start rather than waiting on
	 * buffered data.
	 */
	memset(&wr, 0, sizeof(wr));
	wr.buff_size = PERIOD_BYTES;
	wr.num_buffs = 4;
	wr.start_threshold = 0;
	wr.attributes = GSL_DATA_MODE_BLOCKING;
	rc = gsl_ioctl(graph, GSL_CMD_CONFIGURE_WRITE_PARAMS, &wr, sizeof(wr));
	printf("gsl_ioctl CONFIGURE_WRITE_PARAMS: %d (%s)\n", rc,
	       rc ? "FAILED" : "OK");

	set_media_format(graph, &gkv);

	rc = gsl_ioctl(graph, GSL_CMD_PREPARE, NULL, 0);
	printf("gsl_ioctl PREPARE: %d (%s)\n", rc, rc ? "FAILED" : "OK");

	if (!rc) {
		rc = gsl_ioctl(graph, GSL_CMD_START, NULL, 0);
		printf("gsl_ioctl START: %d (%s)\n", rc, rc ? "FAILED" : "OK");
	}

	if (!rc)
		play_tone(graph);

	gsl_close(graph);
	printf("gsl_close done\n");

	return rc;
}

int main(int argc, char **argv)
{
	struct gsl_acdb_data_files files;
	struct gsl_init_data init;
	uint32_t major, minor;
	int32_t rc;

	if (argc < 2) {
		fprintf(stderr, "usage: %s /abs/path/to.acdb\n", argv[0]);
		return 2;
	}

	ar_log_init();

	gsl_get_version(&major, &minor);
	printf("GSL %u.%u\n", major, minor);

	memset(&files, 0, sizeof(files));
	files.num_files = 1;
	strncpy(files.acdbFiles[0].fileName, argv[1],
		sizeof(files.acdbFiles[0].fileName) - 1);
	files.acdbFiles[0].fileNameLen = strlen(files.acdbFiles[0].fileName);

	memset(&init, 0, sizeof(init));
	init.acdb_files = &files;
	/* Poll for Spf rather than assume it: the ADSP is already up and
	 * serving q6apm, so this should answer on the first or second try. */
	init.max_num_ready_checks = 5;
	init.ready_check_interval_ms = 200;

	rc = gsl_init(&init);
	printf("gsl_init: %d (%s)\n", rc, rc ? "FAILED" : "OK");
	if (rc)
		return 1;

	if (argc > 2)
		rc = open_graph(argc - 2, argv + 2);

	gsl_deinit();
	printf("gsl_deinit done\n");

	return rc ? 1 : 0;
}
