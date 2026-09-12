#!/usr/bin/env bash
# Turn a firmware dump into the tarball the firmware-xiaomi-zeus APKBUILD expects.
# Run after scripts/dump-firmware.sh.
set -euo pipefail

DUMP="${1:-firmware-dump}"
PAY="$DUMP/payload/firmware-xiaomi-zeus"
OUT="src/pmaports/firmware-xiaomi-zeus/firmware-xiaomi-zeus-1.tar.gz"

[ -d "$DUMP/raw" ] || { echo "!! no $DUMP/raw - run ./scripts/dump-firmware.sh first"; exit 1; }

echo "==> merging split firmware (.mdt + .bNN -> .mbn)"
python3 scripts/pil-squash.py "$DUMP/raw" "$DUMP/mbn"

echo "==> assembling payload"
rm -rf "$DUMP/payload"; mkdir -p "$PAY"
cp "$DUMP"/mbn/*.mbn "$PAY"/
cp "$DUMP"/raw/a730_sqe.fw "$DUMP"/raw/a730_zap.mbn "$DUMP"/raw/gmu_gen70000.bin "$PAY"/
cp "$DUMP"/raw/st_fts_l1.ftb "$DUMP"/raw/stm_fts_production_limits.csv "$PAY"/ 2>/dev/null || \
  cp "$DUMP"/touch/st_fts_l1.ftb "$DUMP"/touch/stm_fts_production_limits.csv "$PAY"/
cp -r "$DUMP"/raw/modem_pr "$PAY"/

echo "==> packing $OUT"
mkdir -p "$(dirname "$OUT")"
tar -czf "$OUT" -C "$DUMP/payload" firmware-xiaomi-zeus
ls -la "$OUT"
