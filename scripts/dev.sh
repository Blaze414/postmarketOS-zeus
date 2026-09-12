#!/usr/bin/env bash
# Open a shell in the Linux build container. Run from the repo root on macOS.
#
#   ./scripts/dev.sh          - unprivileged shell, for kernel/dts work
#   ./scripts/dev.sh --priv   - privileged shell, for pmbootstrap image builds
#
# Flash from macOS, not from in here - Docker Desktop has no USB passthrough.
set -euo pipefail

REPO="$(cd "$(dirname "$0")/.." && pwd)"
IMAGE=zeus-build

docker image inspect "$IMAGE" >/dev/null 2>&1 || {
  echo "==> building $IMAGE (one time, a few minutes)"
  docker build --platform linux/arm64 -t "$IMAGE" "$REPO/docker"
}

ARGS=(--rm -it --platform linux/arm64
      -v "$REPO:/work"
      -v zeus-pmb:/home/pmos/.local/var/pmbootstrap
      -v zeus-linux:/src
      -w /work)

if [ "${1:-}" = "--priv" ]; then
  # pmbootstrap needs loop devices and mount. Only for image assembly.
  ARGS+=(--privileged -v /dev:/dev)
  echo "==> privileged mode (pmbootstrap)"
fi

exec docker run "${ARGS[@]}" "$IMAGE" bash
