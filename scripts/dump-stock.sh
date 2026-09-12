#!/usr/bin/env bash
# Pull everything off the stock Xiaomi 12 Pro (zeus) that is needed later.
# Run with the device booted into stock Android, USB debugging on.
# Partition dumps need root (Magisk). The devicetree pull does not.
set -euo pipefail

OUT="${1:-stock-dump}"
mkdir -p "$OUT"

adb wait-for-device

# --- No root needed: the downstream devicetree. Most valuable artifact here. ---
echo "==> pulling live devicetree"
adb pull /sys/firmware/fdt "$OUT/zeus-stock.dtb"
if command -v dtc >/dev/null; then
  dtc -I dtb -O dts "$OUT/zeus-stock.dtb" -o "$OUT/zeus-stock.dts" 2>/dev/null || true
  echo "==> decompiled to $OUT/zeus-stock.dts"
fi

# --- No root needed: hardware inventory, for cross-checking the dts later ---
echo "==> pulling hardware inventory"
{
  echo "### getprop ###";      adb shell getprop
  echo "### /proc/cpuinfo ###"; adb shell cat /proc/cpuinfo
  echo "### partitions ###";    adb shell ls -l /dev/block/by-name/
} > "$OUT/inventory.txt" 2>&1

# --- Root needed from here ---
if ! adb shell su -c 'id' >/dev/null 2>&1; then
  echo "!! no root: skipping partition dumps."
  echo "!! firmware blobs can also be extracted from a stock fastboot ROM instead."
  exit 0
fi

# Firmware/blob partitions. Not the userdata ones - we only want what mainline needs to load.
for p in modem bluetooth dsp abl xbl featenabler devcfg; do
  echo "==> dumping $p"
  adb shell su -c "dd if=/dev/block/by-name/${p}_a of=/sdcard/${p}.img" 2>/dev/null \
    || adb shell su -c "dd if=/dev/block/by-name/${p} of=/sdcard/${p}.img" 2>/dev/null \
    || { echo "   (skipped $p - not present)"; continue; }
  adb pull "/sdcard/${p}.img" "$OUT/${p}.img"
  adb shell su -c "rm /sdcard/${p}.img"
done

echo "==> done. artifacts in $OUT/"
ls -la "$OUT"
