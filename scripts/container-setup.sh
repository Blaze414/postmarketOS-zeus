#!/usr/bin/env bash
# Run INSIDE the build container (./scripts/dev.sh). Clones the kernel into /src,
# which is a Docker volume - ext4, case-sensitive, unlike the macOS host.
set -euo pipefail

if [ ! -d /src ]; then
  echo "!! /src not mounted. Run this inside ./scripts/dev.sh, not on the host."
  exit 1
fi

# Docker creates named volumes root-owned; we run as pmos.
[ -w /src ] || { echo "==> taking ownership of /src"; sudo chown "$(id -u):$(id -g)" /src; }

if [ ! -d /src/linux/.git ]; then
  echo "==> cloning sm8450-mainline/linux (next-new) into the volume"
  git clone --depth=1 -b next-new https://github.com/sm8450-mainline/linux.git /src/linux
else
  echo "==> /src/linux exists"
fi

cd /src/linux
# Sanity: the collision that breaks macOS must be intact here.
n=$(ls net/netfilter/ | grep -ci 'xt_tcpmss' || true)
[ "$n" -eq 2 ] && echo "==> case-sensitivity OK (found $n xt_tcpmss variants)" \
               || { echo "!! case-sensitivity broken in the volume ($n found, expected 2)"; exit 1; }

echo
echo "==> kernel at /src/linux. Our editable sources are bind-mounted at /work."
echo "==> link them in so edits on the Mac land in the build:"
cat <<'MSG'
  ln -sf /work/src/panel/generated/panel-l2-38-0c-0a-dsc.c \
         /src/linux/drivers/gpu/drm/panel/
  ln -sf /work/src/dts/sm8450-xiaomi-zeus.dts \
         /src/linux/arch/arm64/boot/dts/qcom/
MSG
