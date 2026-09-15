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
