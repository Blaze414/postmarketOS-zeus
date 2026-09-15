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

void ar_log_init(void);

#define MAX_KVPS 16

static int32_t open_graph(int nkv, char **kvargs)
{
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

	/* No calibration key vector: the graph's own defaults are enough to
	 * see whether the endpoint gets configured at all. */
	rc = gsl_open(&gkv, NULL, &graph);
	printf("gsl_open: %d (%s)\n", rc, rc ? "FAILED" : "OK");
	if (rc)
		return rc;

	rc = gsl_ioctl(graph, GSL_CMD_PREPARE, NULL, 0);
	printf("gsl_ioctl PREPARE: %d (%s)\n", rc, rc ? "FAILED" : "OK");

	if (!rc) {
		rc = gsl_ioctl(graph, GSL_CMD_START, NULL, 0);
		printf("gsl_ioctl START: %d (%s)\n", rc, rc ? "FAILED" : "OK");
	}

	if (!rc) {
		/* Hold it running for a moment so the DSP's own logs show the
		 * endpoint's steady state, not just its setup. */
		printf("graph running, holding 2s\n");
		sleep(2);
		gsl_ioctl(graph, GSL_CMD_STOP, NULL, 0);
	}

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
