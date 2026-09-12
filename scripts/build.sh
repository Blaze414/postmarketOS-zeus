#!/usr/bin/env bash
# Build zeus artifacts. Run INSIDE the container (./scripts/dev.sh).
#
#   ./scripts/build.sh dtb      - devicetree only (fast)
#   ./scripts/build.sh panel    - compile the panel driver alone
#   ./scripts/build.sh kernel   - full Image.gz + dtbs + modules
#
# Our sources live in /work (bind-mounted from macOS); the kernel lives in
# /src/linux (a Docker volume, because macOS cannot check the tree out correctly).
set -euo pipefail

K=/src/linux
[ -d "$K" ] || { echo "!! no kernel at $K - run ./scripts/container-setup.sh"; exit 1; }
TARGET="${1:-dtb}"
MAKE=(make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j"$(nproc)")

# ---- link our editable sources into the tree ----
ln -sf /work/src/dts/sm8450-xiaomi-zeus.dts    "$K/arch/arm64/boot/dts/qcom/"
ln -sf /work/src/panel/panel-l2-38-0c-0a-dsc.c "$K/drivers/gpu/drm/panel/"

cd "$K"

# ---- register the dtb ----
MK=arch/arm64/boot/dts/qcom/Makefile
grep -q 'sm8450-xiaomi-zeus.dtb' "$MK" || {
  echo "==> registering dtb"
  # NB: the Makefile separates with a TAB, not a space.
  sed -i 's|^\(dtb-\$(CONFIG_ARCH_QCOM)[[:space:]]*+= sm8450-xiaomi-cupid.dtb\)$|\1\ndtb-$(CONFIG_ARCH_QCOM) += sm8450-xiaomi-zeus.dtb|' "$MK"
  grep -q 'sm8450-xiaomi-zeus.dtb' "$MK" || { echo "!! dtb registration FAILED"; exit 1; }
}

# ---- register the panel driver: Kconfig, Makefile, config fragment ----
PK=drivers/gpu/drm/panel/Kconfig
grep -q 'DRM_PANEL_XIAOMI_38_0C_0A' "$PK" || {
  echo "==> registering panel Kconfig"
  python3 - "$PK" <<'PY'
import sys, pathlib
p = pathlib.Path(sys.argv[1]); t = p.read_text()
anchor = "config DRM_PANEL_XINPENG_XPP055C272"
entry = """config DRM_PANEL_XIAOMI_38_0C_0A
	tristate "Xiaomi 38_0C_0A panel driver"
	depends on OF
	depends on DRM_MIPI_DSI
	depends on BACKLIGHT_CLASS_DEVICE
	select VIDEOMODE_HELPERS
	help
		Say Y or M here if you want to enable support for the Xiaomi WQHD
		(3200x1440@120Hz) DSC cmd mode panel found on the Xiaomi 12 Pro.

"""
assert anchor in t, "Kconfig anchor missing"
p.write_text(t.replace(anchor, entry + anchor, 1))
PY
  grep -q 'DRM_PANEL_XIAOMI_38_0C_0A' "$PK" || { echo "!! Kconfig registration FAILED"; exit 1; }
}

PM=drivers/gpu/drm/panel/Makefile
grep -q 'panel-l2-38-0c-0a-dsc.o' "$PM" || {
  echo "==> registering panel Makefile"
  sed -i 's|^\(obj-\$(CONFIG_DRM_PANEL_XIAOMI_42_02_0A) += panel-l3-42-02-0a-dsc.o\)$|\1\nobj-$(CONFIG_DRM_PANEL_XIAOMI_38_0C_0A) += panel-l2-38-0c-0a-dsc.o|' "$PM"
  grep -q 'panel-l2-38-0c-0a-dsc.o' "$PM" || { echo "!! panel Makefile registration FAILED"; exit 1; }
}

FRAG=arch/arm64/configs/sm8450.config
grep -q 'DRM_PANEL_XIAOMI_38_0C_0A' "$FRAG" || {
  echo "==> registering config fragment"
  printf '\n# Xiaomi 12 Pro (Zeus)\nCONFIG_DRM_PANEL_XIAOMI_38_0C_0A=m\n' >> "$FRAG"
}

# ---- config: defconfig + the fork's sm8450 fragment ----
if [ ! -f .config ] || [ "$FRAG" -nt .config ]; then
  echo "==> configuring (defconfig + sm8450.config)"
  make -s ARCH=arm64 defconfig >/dev/null
  ARCH=arm64 scripts/kconfig/merge_config.sh -m -O . .config "$FRAG" >/dev/null
  make -s ARCH=arm64 olddefconfig >/dev/null
fi

grep -q 'CONFIG_DRM_PANEL_XIAOMI_38_0C_0A=m' .config \
  || { echo "!! panel symbol not enabled in .config"; exit 1; }

mkdir -p /work/out
case "$TARGET" in
  dtb)
    echo "==> building dtb"
    "${MAKE[@]}" qcom/sm8450-xiaomi-zeus.dtb
    cp arch/arm64/boot/dts/qcom/sm8450-xiaomi-zeus.dtb /work/out/
    ;;
  panel)
    echo "==> compiling the panel driver alone"
    "${MAKE[@]}" drivers/gpu/drm/panel/panel-l2-38-0c-0a-dsc.o
    ls -la drivers/gpu/drm/panel/panel-l2-38-0c-0a-dsc.o
    ;;
  kernel)
    echo "==> full kernel build"
    "${MAKE[@]}" Image.gz dtbs modules
    cp arch/arm64/boot/Image.gz /work/out/
    cp arch/arm64/boot/dts/qcom/sm8450-xiaomi-zeus.dtb /work/out/
    ;;
  *) echo "!! unknown target: $TARGET"; exit 1 ;;
esac

echo "==> ok: $TARGET"
