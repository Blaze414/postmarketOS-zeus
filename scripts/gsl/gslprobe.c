/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Bring GSL up against the real DSP, control path only.
 *
 * gsl_init() loads the calibration database, registers its GPR ports and then
 * polls Spf for readiness - which is the first thing on this port that has to
 * cross /dev/aud_pasthru_adsp and come back. If that returns, the passthrough
 * and GSL's own transport agree, and the premise of the userspace port holds.
 *
 *   gslprobe /abs/path/Mise_elus_acdb_cal.acdb
 *
 * No graph is opened here and nothing is played: shared memory is the virtual
 * (malloc) backend, which the DSP cannot read.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gsl_intf.h"

void ar_log_init(void);

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

	gsl_deinit();
	printf("gsl_deinit done\n");

	return 0;
}
