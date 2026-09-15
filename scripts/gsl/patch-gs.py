#!/usr/bin/env python3
"""Local edits to a graphservices checkout, applied before building it.

Idempotent: each edit is skipped if its replacement is already present, so
this can be run repeatedly over the same tree.

    patch-gs.py <path to audioreach-graphservices>
"""
import sys
import pathlib

EDITS = [
    (
        "gsl/src/gsl_main.c",
        # gsl_init gives up entirely if the DSP refuses to load the dynamic
        # AMDB modules. On this device those are aptX, LC3 and an Elliptic
        # ultrasound module, and the DSP cannot load any of them: it fetches
        # their .so files from the Android vendor partition over rfsa, which
        # postmarketOS has no counterpart to, so AMDB_CMD_LOAD_MODULES comes
        # back with an error and init fails before anything else is tried.
        #
        # None of them is on the path to the speakers. Treat a load failure
        # the way a missing module list is already treated - note it and keep
        # going. A graph that genuinely needs one of these will fail later at
        # GRAPH_OPEN, where it is visible and attributable.
        """		if (rc != AR_EOK && rc != AR_ENOTEXIST) {
			GSL_ERR("dynamic module load failed %d", rc);
			goto dyn_module_mgr_deinit;
		}""",
        """		if (rc != AR_EOK && rc != AR_ENOTEXIST) {
			GSL_ERR("dynamic module load failed %d, continuing without them",
				rc);
			rc = AR_EOK;
		}""",
    ),
    (
        "gsl/src/gsl_dynamic_module_mgr.c",
        # Skipping the dynamic modules is not the same as attempting them and
        # failing. Registration and load both go to the DSP's AMDB, and both
        # are refused here; whether that leaves AMDB in a state that breaks
        # later graph starts is exactly what needs testing, since every graph
        # - even one with no hardware endpoint - fails at GRAPH_START.
        #
        # Set GSL_SKIP_DYN_MODULES in the environment to not touch AMDB at all.
        """	if (gsl_dyn_mod_mgr_ctxt[master_proc] == NULL)
		goto exit;

	/* TODO: only register if master proc is booting up */""",
        """	if (gsl_dyn_mod_mgr_ctxt[master_proc] == NULL)
		goto exit;

	if (getenv("GSL_SKIP_DYN_MODULES")) {
		GSL_ERR("GSL_SKIP_DYN_MODULES set, leaving AMDB untouched");
		goto exit;
	}

	/* TODO: only register if master proc is booting up */""",
    ),
    (
        "gsl/src/gsl_dynamic_module_mgr.c",
        '#include "gsl_dynamic_module_mgr.h"',
        '#include <stdlib.h>\n#include "gsl_dynamic_module_mgr.h"',
    ),
    (
        "gsl/src/gsl_graph.c",
        # The non-persistent calibration SET_CFG is refused wholesale with
        # AR_EUNSUPPORTED, and GSL only logs the overall result. SPF writes a
        # per-parameter error_code back into the out-of-band payload, which is
        # still mapped here - so walk it and name the parameters that failed.
        """		GSL_ERR("get non-persist data (cal) failed %d", rc);
		goto exit;
	}
""",
        """		GSL_ERR("get non-persist data (cal) failed %d", rc);
		goto exit;
	}

	/*
	 * Drop the entries Spf will not accept at configuration time.
	 *
	 * A subgraph's non-persistent calibration is not purely configuration:
	 * it also carries placeholders the client is expected to fill in, and
	 * runtime commands that only mean something once the graph is running.
	 * Sent verbatim at open, Spf refuses them - and refuses the whole
	 * APM_CMD_SET_CFG with it, so every parameter after the first bad one
	 * goes unapplied and the graph is left half configured. It then opens
	 * and prepares happily and fails at GRAPH_START with a bare error,
	 * which is a long way from the cause.
	 *
	 * Observed on this device, in this order, with the media format first:
	 *   miid 0x458e PARAM_ID_MEDIA_FORMAT   size 12 -> AR_EUNSUPPORTED
	 *   miid 0x4595 PARAM_ID_SOFT_PAUSE_START size 0 -> AR_EFAILED
	 *
	 * Both are dropped by shape rather than by id: a media format whose
	 * payload is empty conveys no format, and a zero-length parameter is a
	 * command rather than a setting. The real media format is sent
	 * separately by the client once the data path is configured.
	 */
	{
		uint8_t *buf = (uint8_t *)gsl_msg.payload;
		uint32_t off = 0, kept = 0;

		while (off + sizeof(apm_module_param_data_t) <=
		       rsp_struct.buf_size) {
			apm_module_param_data_t *p =
				(apm_module_param_data_t *)(buf + off);
			uint32_t len = sizeof(*p) +
				GSL_ALIGN_8BYTE(p->param_size);
			bool_t drop = (p->param_size == 0) ||
				(p->param_id == PARAM_ID_MEDIA_FORMAT &&
				 p->param_size <= sizeof(media_format_t));

			if (off + len > rsp_struct.buf_size)
				break;

			if (drop) {
				GSL_ERR("cal: dropping miid 0x%x pid 0x%x size %d",
					p->module_instance_id, p->param_id,
					p->param_size);
			} else {
				if (kept != off)
					memmove(buf + kept, buf + off, len);
				kept += len;
			}
			off += len;
		}
		rsp_struct.buf_size = kept;
	}
""",
    ),
    (
        "gsl/src/gsl_graph.c",
        # GRAPH_START goes out for every subgraph at once and Spf answers with
        # a single status, so a refusal says nothing about which subgraph is
        # at fault. GSL_START_ONLY_SG=<index> starts just one of them, leaving
        # the rest open and prepared: run it once per index and the failing
        # subgraph names itself.
        """		for (i = 0; i < gkv_node->num_of_subgraphs; ++i) {
			sg = gkv_node->sg_array[i];
			/* send start command only for SGs that are not in START state */
			if (sg && sg->start_ref_cnt == 0) {""",
        """		for (i = 0; i < gkv_node->num_of_subgraphs; ++i) {
			const char *only = getenv("GSL_START_ONLY_SG");

			sg = gkv_node->sg_array[i];
			if (only && i != (uint32_t)atoi(only))
				continue;
			/* send start command only for SGs that are not in START state */
			if (sg && sg->start_ref_cnt == 0) {
				GSL_ERR("start: subgraph[%d] = 0x%x", i, sg->sg_id);""",
    ),
    (
        "gsl/src/gsl_graph.c",
        '#include "acdb.h"',
        '#include <string.h>\n#include <stdlib.h>\n#include "media_fmt_api_basic.h"\n#include "acdb.h"',
    ),
    (
        "gsl/src/gsl_graph.c",
        # and report what Spf refused, whatever survives the filter
        """	if (rc)
		GSL_ERR("send non-perist cal failed %d", rc);""",
        """	if (rc) {
		uint32_t off = 0;

		GSL_ERR("send non-perist cal failed %d", rc);
		while (off + sizeof(apm_module_param_data_t) <=
		       rsp_struct.buf_size) {
			apm_module_param_data_t *p =
				(apm_module_param_data_t *)
				((uint8_t *)gsl_msg.payload + off);

			if (p->error_code)
				GSL_ERR("  cal param miid 0x%x pid 0x%x size %d -> error %d",
					p->module_instance_id, p->param_id,
					p->param_size, p->error_code);
			off += sizeof(*p) + GSL_ALIGN_8BYTE(p->param_size);
		}
	}""",
    ),
]


def main(root):
    root = pathlib.Path(root)
    for rel, old, new in EDITS:
        path = root / rel
        text = path.read_text()
        if new in text:
            print(f"{rel}: already applied")
            continue
        if text.count(old) != 1:
            sys.exit(f"{rel}: expected exactly one match, found {text.count(old)}")
        path.write_text(text.replace(old, new))
        print(f"{rel}: patched")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    main(sys.argv[1])
