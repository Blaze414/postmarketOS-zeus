/* Dump graphs from a stock ACDB: supported GKVs + aliases, and for any GKV whose
 * alias matches argv[2], its subgraphs, subgraph SPF data and connections. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acdb.h"
#include "ar_osal_error.h"

static void hexdump(const unsigned char *p, uint32_t n)
{
	for (uint32_t i = 0; i < n; i += 4) {
		uint32_t v = 0;
		memcpy(&v, p + i, (n - i) >= 4 ? 4 : n - i);
		printf("%s%08x", (i % 32) ? " " : "\n      ", v);
	}
	printf("\n");
}

static int alias(AcdbKeyValuePair *kv, uint32_t n, char *out, uint32_t len)
{
	AcdbGraphKeyVector gkv = { n, kv };
	AcdbString s = { len, out };
	memset(out, 0, len);
	return acdb_ioctl(ACDB_CMD_GET_GRAPH_ALIAS, &gkv, sizeof(gkv), &s, sizeof(s));
}

int main(int argc, char **argv)
{
	AcdbDataFiles files = { 1 };
	int32_t rc;

	if (argc < 2) { fprintf(stderr, "usage: acdbq file.acdb [alias-substring]\n"); return 1; }
	strncpy(files.acdbFiles[0].fileName, argv[1], sizeof(files.acdbFiles[0].fileName) - 1);
	files.acdbFiles[0].fileNameLen = strlen(argv[1]);
	rc = acdb_init(&files, NULL);
	printf("acdb_init rc=%d\n", rc);
	if (rc) return 1;

	AcdbUintList keys = { 0, NULL };
	AcdbKeyVectorList kvl = { 0 };
	rc = acdb_ioctl(ACDB_CMD_GET_SUPPORTED_GKVS, &keys, sizeof(keys), &kvl, sizeof(kvl));
	printf("supported gkvs rc=%d n=%u size=%u\n", rc, kvl.num_key_vectors, kvl.list_size);
	kvl.key_vector_list = malloc(kvl.list_size);
	rc = acdb_ioctl(ACDB_CMD_GET_SUPPORTED_GKVS, &keys, sizeof(keys), &kvl, sizeof(kvl));

	uint32_t *p = (uint32_t *)kvl.key_vector_list;
	char name[512];
	for (uint32_t g = 0; g < kvl.num_key_vectors; g++) {
		uint32_t nk = *p++;
		AcdbKeyValuePair *kv = (AcdbKeyValuePair *)p;
		p += 2 * nk;
		alias(kv, nk, name, sizeof(name));
		char kvs[1024] = ""; for (uint32_t k = 0; k < nk; k++) sprintf(kvs + strlen(kvs), " %08x=%08x", kv[k].key, kv[k].value);
		if (argc < 3) { printf("GKV %u:%s\n", g, kvs); continue; }
		if (strcmp(kvs, argv[2])) continue;

		printf("\n===== GKV %u: %s\n  keys:", g, name);
		for (uint32_t k = 0; k < nk; k++) printf(" %08x=%08x", kv[k].key, kv[k].value);
		printf("\n");

		AcdbGraphKeyVector gkv = { nk, kv };
		AcdbGetGraphRsp gr = { 0 };
		rc = acdb_ioctl(ACDB_CMD_GET_GRAPH, &gkv, sizeof(gkv), &gr, sizeof(gr));
		gr.subgraphs = malloc(gr.size);
		rc = acdb_ioctl(ACDB_CMD_GET_GRAPH, &gkv, sizeof(gkv), &gr, sizeof(gr));
		printf("  graph rc=%d subgraphs=%u\n", rc, gr.num_subgraphs);
		uint32_t *sp = (uint32_t *)gr.subgraphs, sgids[64];
		for (uint32_t s = 0; s < gr.num_subgraphs && s < 64; s++) {
			sgids[s] = sp[0];
			printf("    sg %08x -> dst:", sp[0]);
			for (uint32_t d = 0; d < sp[1]; d++) printf(" %08x", sp[2 + d]);
			printf("\n");
			sp += 2 + sp[1];
		}

		AcdbSgIdGraphKeyVector req = { gr.num_subgraphs, sgids, gkv };
		AcdbGetSubgraphDataRsp sd = { 0 };
		rc = acdb_ioctl(ACDB_CMD_GET_SUBGRAPH_DATA, &req, sizeof(req), &sd, sizeof(sd));
		sd.driver_prop.sub_graph_prop_data = malloc(sd.driver_prop.size ? sd.driver_prop.size : 4);
		sd.spf_blob.buf = malloc(sd.spf_blob.buf_size ? sd.spf_blob.buf_size : 4);
		rc = acdb_ioctl(ACDB_CMD_GET_SUBGRAPH_DATA, &req, sizeof(req), &sd, sizeof(sd));
		printf("  subgraph data rc=%d spf_blob=%u bytes:", rc, sd.spf_blob.buf_size);
		hexdump(sd.spf_blob.buf, sd.spf_blob.buf_size);

		{
			AcdbKeyValuePair none[1];
			AcdbSgIdCalKeyVector ck = { gr.num_subgraphs, sgids, { 0, none }, { 0, none } };
			AcdbBlob cal = { 0 };
			rc = acdb_ioctl(ACDB_CMD_GET_SUBGRAPH_CALIBRATION_DATA_NONPERSIST, &ck, sizeof(ck), &cal, sizeof(cal));
			printf("  cal(nonpersist, no ckv) rc=%d size=%u\n", rc, cal.buf_size);
			if (cal.buf_size) {
				cal.buf = malloc(cal.buf_size);
				rc = acdb_ioctl(ACDB_CMD_GET_SUBGRAPH_CALIBRATION_DATA_NONPERSIST, &ck, sizeof(ck), &cal, sizeof(cal));
				unsigned char *c = cal.buf; uint32_t o = 0;
				while (o + 16 <= cal.buf_size) {
					uint32_t iid, pid, sz, err;
					memcpy(&iid, c + o, 4); memcpy(&pid, c + o + 4, 4); memcpy(&sz, c + o + 8, 4); memcpy(&err, c + o + 12, 4);
					o += 16;
					printf("    cal iid=%x pid=%08x size=%u:", iid, pid, sz);
					hexdump(c + o, sz);
					o += (sz + 7) & ~7u;
				}
			}
		}
		{
			AcdbKeyVectorList cl = { 0 };
			rc = acdb_ioctl(ACDB_CMD_GET_GRAPH_CAL_KVS, &gkv, sizeof(gkv), &cl, sizeof(cl));
			printf("  cal kvs rc=%d n=%u size=%u\n", rc, cl.num_key_vectors, cl.list_size);
			if (cl.list_size) {
				cl.key_vector_list = malloc(cl.list_size);
				rc = acdb_ioctl(ACDB_CMD_GET_GRAPH_CAL_KVS, &gkv, sizeof(gkv), &cl, sizeof(cl));
				uint32_t *q = (uint32_t *)cl.key_vector_list;
				for (uint32_t c = 0; c < cl.num_key_vectors; c++) {
					uint32_t nck = *q++;
					AcdbKeyValuePair *ckv = (AcdbKeyValuePair *)q; q += 2 * nck;
					printf("   ckv:"); for (uint32_t k = 0; k < nck; k++) printf(" %08x=%08x", ckv[k].key, ckv[k].value); printf("\n");
					AcdbKeyValuePair none[1];
					AcdbSgIdCalKeyVector ck = { gr.num_subgraphs, sgids, { 0, none }, { nck, ckv } };
					AcdbBlob cal = { 0 };
					rc = acdb_ioctl(ACDB_CMD_GET_SUBGRAPH_CALIBRATION_DATA_NONPERSIST, &ck, sizeof(ck), &cal, sizeof(cal));
					if (!cal.buf_size) continue;
					cal.buf = malloc(cal.buf_size);
					rc = acdb_ioctl(ACDB_CMD_GET_SUBGRAPH_CALIBRATION_DATA_NONPERSIST, &ck, sizeof(ck), &cal, sizeof(cal));
					unsigned char *cc = cal.buf; uint32_t o = 0;
					while (o + 16 <= cal.buf_size) {
						uint32_t iid, pid, sz; memcpy(&iid, cc + o, 4); memcpy(&pid, cc + o + 4, 4); memcpy(&sz, cc + o + 8, 4); o += 16;
						printf("     cal iid=%x pid=%08x size=%u:", iid, pid, sz); hexdump(cc + o, sz); o += (sz + 7) & ~7u;
					}
				}
			}
		}
		AcdbSubGraphList sgl = { gr.num_subgraphs, gr.subgraphs };
		AcdbBlob cb = { 0 };
		rc = acdb_ioctl(ACDB_CMD_GET_SUBGRAPH_CONNECTIONS, &sgl, sizeof(sgl), &cb, sizeof(cb));
		cb.buf = malloc(cb.buf_size ? cb.buf_size : 4);
		rc = acdb_ioctl(ACDB_CMD_GET_SUBGRAPH_CONNECTIONS, &sgl, sizeof(sgl), &cb, sizeof(cb));
		printf("  connections rc=%d %u bytes:", rc, cb.buf_size);
		hexdump(cb.buf, cb.buf_size);
	}
	return 0;
}
