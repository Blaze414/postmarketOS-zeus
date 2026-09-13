#!/usr/bin/env bash
# Clone the downstream (Android 5.10) kernel for the Option B port.
# Run INSIDE the container. Everything lands in /src, which is ext4 and
# case-sensitive - the macOS side cannot hold a kernel tree.
set -euo pipefail

D=/src/downstream
mkdir -p "$D"

clone() {
  [ -d "$2/.git" ] && { echo "==> $2 exists"; return; }
  echo "==> cloning $2"
  git clone --depth=1 -b "$3" "$1" "$2"
}

clone https://github.com/LineageOS/android_kernel_xiaomi_sm8450.git \
      "$D/kernel" lineage-23.2
clone https://github.com/LineageOS/android_kernel_xiaomi_sm8450-devicetrees.git \
      "$D/devicetrees" lineage-23.2

echo "==> kernel version"
make -s -C "$D/kernel" kernelversion
echo "==> devicetree layout"
ls "$D/devicetrees" | head
find "$D/devicetrees" -iname '*zeus*' | head -5
