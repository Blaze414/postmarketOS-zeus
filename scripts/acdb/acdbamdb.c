/* Dump the AMDB (dynamic DSP module) registration and boot-load data that
 * graphservices sends to the DSP at init.  acdbamdb /abs/file.acdb */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acdb.h"

static void dump(const char *what, uint32_t cmd, uint32_t proc)
{
	AcdbAmdbProcID req = { proc };
	AcdbBlob b = { 0, NULL };
	int rc = acdb_ioctl(cmd, &req, sizeof(req), &b, sizeof(b));

	printf("%s proc %u rc=%d size=%u\n", what, proc, rc, b.buf_size);
	if (rc || !b.buf_size)
		return;
	b.buf = calloc(1, b.buf_size + 8);
	acdb_ioctl(cmd, &req, sizeof(req), &b, sizeof(b));
	unsigned char *p = b.buf;
	for (uint32_t i = 0; i < b.buf_size; i += 4) {
		uint32_t v; memcpy(&v, p + i, 4);
		printf("%s%08x", (i % 32) ? " " : "\n  ", v);
	}
	printf("\n  ascii:");
	for (uint32_t i = 0; i < b.buf_size; i++)
		putchar(p[i] >= 32 && p[i] < 127 ? p[i] : (p[i] ? '.' : ' '));
	printf("\n");
}

int main(int argc, char **argv)
{
	AcdbDataFiles files = { 1 };

	strncpy(files.acdbFiles[0].fileName, argv[1], sizeof(files.acdbFiles[0].fileName) - 1);
	files.acdbFiles[0].fileNameLen = strlen(argv[1]);
	if (acdb_init(&files, NULL)) return 1;
	for (uint32_t proc = 1; proc <= 4; proc++) {
		dump("REG", ACDB_CMD_GET_AMDB_REGISTRATION_DATA, proc);
		dump("BOOTLOAD", ACDB_CMD_GET_AMDB_BOOTUP_LOAD_MODULES, proc);
	}
	return 0;
}
