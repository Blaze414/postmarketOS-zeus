#!/usr/bin/env bash
# Generate a mainline DRM panel driver from the downstream panel node.
#
# Wraps msm8916-mainline/linux-mdss-dsi-panel-driver-generator, which turns a
# qcom,mdss-dsi-* node (with its hex DCS init command stream) into a mainline
# drivers/gpu/drm/panel/ driver. Hand-transcribing the init stream is how ports die.
set -euo pipefail

REPO="$(cd "$(dirname "$0")/.." && pwd)"
GEN="$REPO/upstream/panel-generator"
NODE="$REPO/src/panel/zeus-panel-node.dts"
OUT="$REPO/src/panel/generated"

[ -f "$NODE" ] || { echo "!! missing $NODE"; exit 1; }

if [ ! -d "$GEN/.git" ]; then
  echo "==> cloning panel driver generator"
  git clone --depth=1 https://github.com/msm8916-mainline/linux-mdss-dsi-panel-driver-generator.git "$GEN"
fi

mkdir -p "$OUT"
cd "$GEN"
python3 gen-panel-driver.py --dsi --outdir "$OUT" "$NODE" || {
  echo
  echo "!! generator rejected the node."
  echo "!! It expects a standalone .dtsi with the panel node at top level."
  echo "!! Common fix: wrap the node in '/ { ... };' and strip the phandle = <...> lines."
  exit 1
}

echo "==> generated into $OUT"
ls -la "$OUT"
cat <<'MSG'

Next, by hand (the generator cannot know these):
  - replace the drm_display_mode block with the one in src/panel/README.md
  - set the DSC config in probe() per src/panel/README.md
  - drop MIPI_DSI_MODE_VIDEO_BURST - zeus is a command-mode panel
  - rename the compatible to "mdss,l2-38-0c-0a-dsc"
MSG
