#!/usr/bin/env bash
# Clone the upstream trees this port builds on. Run on the Linux build host.
set -euo pipefail

ROOT="${1:-$PWD/upstream}"
mkdir -p "$ROOT"
cd "$ROOT"

clone() {  # clone <url> <dir> <branch>
  if [ -d "$2/.git" ]; then
    echo "==> $2 exists, fetching"; git -C "$2" fetch --depth=1 origin "$3"
  else
    echo "==> cloning $2 ($3)"; git clone --depth=1 -b "$3" "$1" "$2"
  fi
}

# Mainline kernel fork carrying SM8450 device support (cupid lives here).
clone https://github.com/sm8450-mainline/linux.git            linux      next-new

# pmaports fork with the sm8450 device packages.
clone https://github.com/sm8450-mainline/pmaports.git         pmaports   master

# Nonfree firmware blobs for zeus specifically.
clone https://github.com/sm8450-mainline/firmware-xiaomi-zeus.git firmware-xiaomi-zeus main

# Downstream devicetrees extracted from MIUI/HyperOS/LineageOS - cross-reference material.
clone https://github.com/sm8450-mainline/fdt.git              fdt        master

# Official LineageOS device tree - authoritative on partition layout and hardware parts.
clone https://github.com/LineageOS/android_device_xiaomi_zeus.git los-zeus lineage-23.2

cat <<'MSG'

==> done.

Reference files you will live in:
  upstream/linux/arch/arm64/boot/dts/qcom/sm8450-xiaomi-cupid.dts   <- your template
  upstream/linux/arch/arm64/boot/dts/qcom/sm8450.dtsi               <- SoC base
  upstream/pmaports/device/testing/device-xiaomi-cupid/             <- package template
  upstream/los-zeus/                                                <- zeus hardware truth
MSG
