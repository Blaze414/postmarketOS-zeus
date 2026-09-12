#!/usr/bin/env bash
# Pull the proprietary firmware zeus needs for GPU, DSP, modem and IPA off the
# running device. Needs root (the device has KernelSU).
#
# Upstream has no firmware-xiaomi-zeus repo - it is an empty repository, and
# git.mainlining.org (where cupid's lives) is returning 502 - so we extract from
# the device instead. These blobs are Xiaomi's; they stay gitignored.
set -euo pipefail

OUT="${1:-firmware-dump}"
mkdir -p "$OUT/raw"
adb wait-for-device
adb shell su -c 'id' >/dev/null || { echo "!! need root"; exit 1; }

STAGE=/sdcard/zeusfw
adb shell su -c "rm -rf $STAGE; mkdir -p $STAGE"

echo "==> staging GPU firmware"
adb shell su -c "cp /vendor/firmware/a730_sqe.fw /vendor/firmware/a730_zap.mbn \
                    /vendor/firmware/gmu_gen70000.bin $STAGE/"

echo "==> staging remoteproc + ipa firmware"
# adsp/cdsp/slpi/modem/ipa ship split: a .mdt header plus .b00..bNN segments.
for p in adsp cdsp slpi modem ipa_fws; do
  adb shell su -c "cp /vendor/firmware_mnt/image/${p}.mdt /vendor/firmware_mnt/image/${p}.b* $STAGE/ 2>/dev/null" || true
done
# modem_pr is a directory of extra modem payloads, copied wholesale by cupid too.
adb shell su -c "cp -r /vendor/firmware_mnt/image/modem_pr $STAGE/ 2>/dev/null" || true

echo "==> pulling"
adb shell su -c "chmod -R 0777 $STAGE"
adb pull "$STAGE" "$OUT/raw" >/dev/null
adb shell su -c "rm -rf $STAGE"

mv "$OUT/raw/zeusfw/"* "$OUT/raw/" 2>/dev/null || true
rmdir "$OUT/raw/zeusfw" 2>/dev/null || true
echo "==> pulled:"
du -sh "$OUT/raw"
ls "$OUT/raw" | sed 's/\..*//' | sort -u | tr '\n' ' '; echo
