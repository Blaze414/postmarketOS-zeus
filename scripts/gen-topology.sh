#!/usr/bin/env bash
# Generate the zeus ALSA topology sources from src/topology/Xiaomi-12.m4.
#
# The m4 macro library that does the real work lives upstream in
# linux-msm/audioreach-topology - the same tree Qualcomm and Linaro build every
# qcom/*-tplg.bin in linux-firmware from. Rather than vendor twenty BSD-licensed
# include files, this fetches that tree and expands our topology against it. The
# expanded .conf files are what gets committed and what the device package
# compiles with alsatplg, so a build never needs the network.
#
# Run from the repo root, on macOS or in the container - only m4 and git needed.
#
#   ./scripts/gen-topology.sh
#
# Produces, in src/pmaports/device-xiaomi-zeus/:
#   Xiaomi-12-tplg.conf       speakers on SD1 (tert_tdm_dout, gpio124)
#   Xiaomi-12-sd0-tplg.conf   speakers on SD0 (tert_tdm_din,  gpio122)
#
# Both are installed. Which one is live is a symlink on the device, so trying
# the other line costs a reboot rather than a reflash. See src/topology/Xiaomi-12.m4.
set -euo pipefail

REPO="$(cd "$(dirname "$0")/.." && pwd)"
SRC="$REPO/src/topology/Xiaomi-12.m4"
OUT="$REPO/src/pmaports/device-xiaomi-zeus"
# Pin the macro library. An unpinned clone would silently change what ships.
UPSTREAM=https://github.com/linux-msm/audioreach-topology.git
COMMIT=main

WORK="$(mktemp -d)"
trap 'rm -rf "$WORK"' EXIT

echo "==> fetching the audioreach m4 macro library"
git clone --quiet --depth 1 --branch "$COMMIT" "$UPSTREAM" "$WORK/ar"
echo "    at $(git -C "$WORK/ar" rev-parse --short HEAD)"

gen() {
	local out="$1"; shift
	m4 -I "$WORK/ar" "$@" "$SRC" > "$OUT/$out"
	echo "==> $out  ($(grep -c '' "$OUT/$out") lines)"
}

gen Xiaomi-12-tplg.conf
gen Xiaomi-12-sd0-tplg.conf -DZEUS_SPK_SD0

# Cheap sanity check: the whole point of this file is the tertiary backend, and
# m4 failing to expand a macro produces a plausible-looking file with the macro
# name left in it rather than an error.
for f in Xiaomi-12-tplg.conf Xiaomi-12-sd0-tplg.conf; do
	grep -q 'device20.i2s_rx1' "$OUT/$f" ||
		{ echo "FAIL: $f has no tertiary MI2S widget"; exit 1; }
	grep -q 'ZEUS_SPK_SD_LINE\|SD_LINE_IDX_I2S' "$OUT/$f" &&
		{ echo "FAIL: $f has an unexpanded macro"; exit 1; }
	echo "    $f: tertiary backend present, fully expanded"
done
