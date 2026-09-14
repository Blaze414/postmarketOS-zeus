/* Dump module-tag data (what AGM's gsl_get_tagged_data returns) for one GKV:
 * tags -> modules, tag key vectors, and each tagged payload.
 *   acdbtag /abs/file.acdb a1000000=a1000003 a2000000=a2000001 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acdb.h"

static void hexdump(const unsigned char *p, uint32_t n)
{
	for (uint32_t i = 0; i < n; i += 4) {
		uint32_t v = 0;
		memcpy(&v, p + i, (n - i) >= 4 ? 4 : n - i);
		printf("%s%08x", (i % 32) ? " " : "\n      ", v);
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	AcdbDataFiles files = { 1 };
	AcdbKeyValuePair kv[8];
	uint32_t nk = 0;

	strncpy(files.acdbFiles[0].fileName, argv[1], sizeof(files.acdbFiles[0].fileName) - 1);
	files.acdbFiles[0].fileNameLen = strlen(argv[1]);
	if (acdb_init(&files, NULL)) return 1;
	for (int i = 2; i < argc && nk < 8; i++, nk++)
		sscanf(argv[i], "%x=%x", &kv[nk].key, &kv[nk].value);
	AcdbGraphKeyVector gkv = { nk, kv };

	AcdbCmdGetTagsFromGkvReq treq = { &gkv };
	AcdbCmdGetTagsFromGkvRsp trsp = { 0 };
	int rc = acdb_ioctl(ACDB_CMD_GET_TAGS_FROM_GKV, &treq, sizeof(treq), &trsp, sizeof(trsp));
	trsp.tag_module_list = malloc(trsp.list_size + 4);
	rc = acdb_ioctl(ACDB_CMD_GET_TAGS_FROM_GKV, &treq, sizeof(treq), &trsp, sizeof(trsp));
	printf("tags rc=%d n=%u\n", rc, trsp.num_tags);
	uint32_t *p = (uint32_t *)trsp.tag_module_list;
	for (uint32_t t = 0; t < trsp.num_tags; t++) {
		printf("  tag %08x:", p[0]);
		for (uint32_t m = 0; m < p[1]; m++) printf(" %08x/%x", p[2 + 2 * m], p[3 + 2 * m]);
		printf("\n");
		p += 2 + 2 * p[1];
	}

	AcdbTagKeyVectorList kl = { 0 };
	rc = acdb_ioctl(ACDB_CMD_GET_GRAPH_TAG_KVS, &gkv, sizeof(gkv), &kl, sizeof(kl));
	kl.key_vector_list = malloc(kl.list_size + 4);
	rc = acdb_ioctl(ACDB_CMD_GET_GRAPH_TAG_KVS, &gkv, sizeof(gkv), &kl, sizeof(kl));
	printf("tag kvs rc=%d n=%u\n", rc, kl.num_key_vectors);

	AcdbGetGraphRsp gr = { 0 };
	acdb_ioctl(ACDB_CMD_GET_GRAPH, &gkv, sizeof(gkv), &gr, sizeof(gr));
	gr.subgraphs = malloc(gr.size);
	acdb_ioctl(ACDB_CMD_GET_GRAPH, &gkv, sizeof(gkv), &gr, sizeof(gr));
	uint32_t sgids[16], *sp = (uint32_t *)gr.subgraphs;
	for (uint32_t s = 0; s < gr.num_subgraphs; s++) { sgids[s] = sp[0]; sp += 2 + sp[1]; }

	p = (uint32_t *)kl.key_vector_list;
	for (uint32_t k = 0; k < kl.num_key_vectors; k++) {
		uint32_t tag = p[0], n = p[1];
		printf("  tag %08x keys:", tag);
		for (uint32_t i = 0; i < n; i++) printf(" %08x=%08x", p[2 + 2 * i], p[3 + 2 * i]);
		AcdbSgIdModuleTag req = { gr.num_subgraphs, sgids, { tag, { n, (AcdbKeyValuePair *)(p + 2) } } };
		AcdbBlob b = { 0, NULL };
		rc = acdb_ioctl(ACDB_CMD_GET_MODULE_TAG_DATA, &req, sizeof(req), &b, sizeof(b));
		printf("  -> rc=%d size=%u", rc, b.buf_size);
		if (!rc && b.buf_size) {
			b.buf = malloc(b.buf_size);
			rc = acdb_ioctl(ACDB_CMD_GET_MODULE_TAG_DATA, &req, sizeof(req), &b, sizeof(b));
			hexdump(b.buf, b.buf_size);
		} else {
			printf("\n");
		}
		p += 2 + 2 * n;
	}
	return 0;
}
