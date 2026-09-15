/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Smallest possible exercise of /dev/aud_pasthru_adsp.
 *
 * Sends APM_CMD_GET_SPF_STATE to the ADSP's audio process manager and waits
 * for APM_CMD_RSP_GET_SPF_STATE - the same handshake q6apm does at probe. It
 * proves the whole passthrough round trip (write -> rpmsg -> DSP -> router ->
 * port lookup -> read) without dragging in GSL, its ACDB or shared memory.
 *
 *   aarch64-linux-gnu-gcc -O2 -static -o gprprobe gprprobe.c
 *
 * A GPR packet is six header words followed by the payload:
 *   w0  version:4 | hdr_size:4 (words) | pkt_size:24 (bytes)
 *   w1  dest_domain:8 | src_domain:8 | reserved:16
 *   w2  src_port   w3 dest_port   w4 token   w5 opcode
 */
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define DEV			"/dev/aud_pasthru_adsp"

#define GPR_DOMAIN_ID_ADSP	2
#define GPR_DOMAIN_ID_APPS	3
#define APM_MODULE_INSTANCE_ID	1

#define APM_CMD_GET_SPF_STATE		0x01001021
#define APM_CMD_RSP_GET_SPF_STATE	0x02001007
#define GPR_BASIC_RSP_RESULT		0x02001005

/* GSL_MAIN_SRC_PORT, so this also exercises the id the real client uses. */
#define SRC_PORT		0x2003
#define TOKEN			0x5a5a0001

#define HDR_WORDS		6
#define BUF_SIZE		4096

int main(void)
{
	uint32_t pkt[HDR_WORDS];
	uint8_t buf[BUF_SIZE];
	struct pollfd pfd;
	uint32_t *r;
	int fd, n;

	fd = open(DEV, O_RDWR);
	if (fd < 0) {
		fprintf(stderr, "open %s: %s\n", DEV, strerror(errno));
		return 1;
	}

	pkt[0] = 0 | (HDR_WORDS << 4) | (sizeof(pkt) << 8);
	pkt[1] = GPR_DOMAIN_ID_ADSP | (GPR_DOMAIN_ID_APPS << 8);
	pkt[2] = SRC_PORT;
	pkt[3] = APM_MODULE_INSTANCE_ID;
	pkt[4] = TOKEN;
	pkt[5] = APM_CMD_GET_SPF_STATE;

	printf("tx %zu bytes: %08x %08x %08x %08x %08x %08x\n", sizeof(pkt),
	       pkt[0], pkt[1], pkt[2], pkt[3], pkt[4], pkt[5]);

	n = write(fd, pkt, sizeof(pkt));
	if (n != (int)sizeof(pkt)) {
		fprintf(stderr, "write: %d (%s)\n", n, strerror(errno));
		return 1;
	}

	pfd.fd = fd;
	pfd.events = POLLIN;
	n = poll(&pfd, 1, 2000);
	if (n <= 0) {
		fprintf(stderr, "no reply within 2s (poll=%d %s)\n", n,
			n < 0 ? strerror(errno) : "timeout");
		return 1;
	}

	n = read(fd, buf, sizeof(buf));
	if (n < (int)sizeof(pkt)) {
		fprintf(stderr, "read: %d (%s)\n", n, strerror(errno));
		return 1;
	}

	r = (uint32_t *)buf;
	printf("rx %d bytes: %08x %08x %08x %08x %08x %08x", n,
	       r[0], r[1], r[2], r[3], r[4], r[5]);
	for (int i = HDR_WORDS; i < n / 4; i++)
		printf(" %08x", r[i]);
	printf("\n");

	printf("opcode %08x dest_port %08x token %08x\n", r[5], r[3], r[4]);

	if (r[5] == APM_CMD_RSP_GET_SPF_STATE) {
		/* payload[0]: 0 = not ready, 1 = ready. */
		printf("OK: SPF state = %u\n", n > 24 ? r[6] : 0);
		return 0;
	}
	if (r[5] == GPR_BASIC_RSP_RESULT) {
		printf("basic response: opcode %08x status %08x\n", r[6], r[7]);
		return 1;
	}
	printf("unexpected opcode\n");
	return 1;
}
