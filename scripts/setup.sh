#!/usr/bin/env bash
# Host-side clones. Run from the repo root on macOS.
#
# The Linux kernel tree is deliberately NOT cloned here - macOS APFS is
# case-insensitive and the kernel contains colliding filenames
# (net/netfilter/xt_TCPMSS.c vs xt_tcpmss.c, and 12 more). Git checks out one,
# silently clobbers the other, and leaves a tree that looks fine but is not.
# The kernel lives inside the build container instead: scripts/container-setup.sh
set -euo pipefail

ROOT="${1:-$PWD/upstream}"
mkdir -p "$ROOT"
cd "$ROOT"

clone() {  # clone <url> <dir> <branch>
  if [ -d "$2/.git" ]; then
    echo "==> $2 exists, fetching"; git -C "$2" fetch --depth=1 origin "$3" || echo "!! fetch failed for $2"
  else
    echo "==> cloning $2 ($3)"
    git clone --depth=1 -b "$3" "$1" "$2" || echo "!! CLONE FAILED: $2 - continuing"
  fi
}

# pmaports fork with the sm8450 device packages (device-xiaomi-cupid is our template).
clone https://github.com/sm8450-mainline/pmaports.git         pmaports   master

# Downstream devicetrees extracted from MIUI/HyperOS - cross-reference for our own dump.
clone https://github.com/sm8450-mainline/fdt.git              fdt        main

# Official LineageOS device tree - authoritative on partition layout and hardware parts.
clone https://github.com/LineageOS/android_device_xiaomi_zeus.git los-zeus lineage-23.2

# NOTE: sm8450-mainline/firmware-xiaomi-zeus is an EMPTY repo (size 0, no branches).
# Not cloned. We have our own blobs in stock-dump/ pulled off the device instead.

echo
echo "==> host-side done. Kernel tree: run ./scripts/dev.sh then ./scripts/container-setup.sh"
