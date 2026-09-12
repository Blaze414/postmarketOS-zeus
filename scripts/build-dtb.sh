#!/usr/bin/env bash
# Build the zeus devicetree. Run INSIDE the container (./scripts/dev.sh).
# Our sources live in /work (bind-mounted from macOS); the kernel lives in
# /src/linux (a Docker volume, because macOS cannot check it out correctly).
set -euo pipefail

K=/src/linux
[ -d "$K" ] || { echo "!! no kernel at $K - run ./scripts/container-setup.sh"; exit 1; }

# Link our editable sources into the tree so edits on the Mac land in the build.
ln -sf /work/src/dts/sm8450-xiaomi-zeus.dts       "$K/arch/arm64/boot/dts/qcom/"
ln -sf /work/src/panel/panel-l2-38-0c-0a-dsc.c    "$K/drivers/gpu/drm/panel/"

cd "$K"

# Register the dtb if it is not already there.
MK=arch/arm64/boot/dts/qcom/Makefile
grep -q 'sm8450-xiaomi-zeus.dtb' "$MK" || {
  echo "==> registering sm8450-xiaomi-zeus.dtb"
  # NB: the Makefile separates with a TAB, not a space.
  sed -i 's|^\(dtb-\$(CONFIG_ARCH_QCOM)[[:space:]]*+= sm8450-xiaomi-cupid.dtb\)$|\1\ndtb-$(CONFIG_ARCH_QCOM) += sm8450-xiaomi-zeus.dtb|' "$MK"
  grep -q 'sm8450-xiaomi-zeus.dtb' "$MK" || { echo "!! Makefile registration FAILED"; exit 1; }
  grep -n 'sm8450-xiaomi' "$MK"
}

[ -f .config ] || { echo "==> defconfig"; make -s ARCH=arm64 defconfig; }

echo "==> building dtb"
make -s ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j"$(nproc)" qcom/sm8450-xiaomi-zeus.dtb

OUT=arch/arm64/boot/dts/qcom/sm8450-xiaomi-zeus.dtb
ls -la "$OUT"
mkdir -p /work/out && cp "$OUT" /work/out/
echo "==> copied to out/$(basename $OUT)"
