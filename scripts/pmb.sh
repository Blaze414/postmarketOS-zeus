#!/usr/bin/env bash
# Build the zeus postmarketOS image with pmbootstrap.
# Run INSIDE the privileged container:  ./scripts/dev.sh --priv
#
#   /work/scripts/pmb.sh setup    - pmaports + config only
#   /work/scripts/pmb.sh build    - setup, then build the image (long)
#
# Everything persistent lives in /src (a Docker volume): the container's $HOME
# is ephemeral, so the pmbootstrap config must not live there.
set -euo pipefail

APORTS=/src/pmaports-zeus
WORK=/src/pmb-work
CFG=/src/pmbootstrap.cfg
WORK_VERSION=8
ACTION="${1:-build}"

# pmbootstrap 3.x ignores the `aports` config value and looks under its own work
# dir, and -c is needed because $HOME does not survive the container. Pass all three.
PMB=(pmbootstrap -c "$CFG" -p "$APORTS" -w "$WORK")

[ -w /src ] || sudo chown "$(id -u):$(id -g)" /src

# --- pmaports ---
if [ ! -d "$APORTS/.git" ]; then
  echo "==> cloning pmaports fork"
  git clone --depth=1 https://github.com/sm8450-mainline/pmaports.git "$APORTS"
fi

# pmbootstrap requires a remote pointing at the canonical pmaports URL, and reads
# channels.cfg from <that remote>/main, so the ref has to exist locally too.
if ! git -C "$APORTS" remote -v | grep -q 'gitlab.postmarketos.org/postmarketOS/pmaports'; then
  git -C "$APORTS" remote add postmarketOS https://gitlab.postmarketos.org/postmarketOS/pmaports.git
fi
git -C "$APORTS" rev-parse --verify -q postmarketOS/main >/dev/null || {
  echo "==> fetching canonical pmaports main (for channels.cfg)"
  git -C "$APORTS" fetch --depth=1 postmarketOS main
}

# --- our packages, refreshed from /work every run ---
echo "==> installing zeus packages into pmaports"
for p in device-xiaomi-zeus linux-postmarketos-qcom-sm8450-zeus; do
  rm -rf "$APORTS/device/testing/$p"
  cp -r "/work/src/pmaports/$p" "$APORTS/device/testing/$p"
done

# --- work folder ---
# `pmbootstrap init` is interactive with no non-interactive equivalent, but all
# it does to the work folder is create it and stamp a version marker.
if [ ! -f "$WORK/version" ]; then
  echo "==> creating work folder (version $WORK_VERSION)"
  sudo rm -rf "$WORK"; mkdir -p "$WORK"; echo "$WORK_VERSION" > "$WORK/version"
fi

# --- config ---
if [ ! -f "$CFG" ]; then
  echo "==> seeding $CFG"
  printf '[pmbootstrap]\naports = %s\nwork = %s\n' "$APORTS" "$WORK" > "$CFG"
fi
"${PMB[@]}" config device xiaomi-zeus
"${PMB[@]}" config kernel postmarketos-qcom-sm8450-zeus
"${PMB[@]}" config ui console       # console first: a failed desktop looks like a failed boot
"${PMB[@]}" config systemd never
"${PMB[@]}" config user pmos
"${PMB[@]}" config hostname zeus
"${PMB[@]}" config jobs "$(nproc)"

echo "==> checksums"
"${PMB[@]}" -y checksum linux-postmarketos-qcom-sm8450-zeus device-xiaomi-zeus
for p in device-xiaomi-zeus linux-postmarketos-qcom-sm8450-zeus; do
  cp "$APORTS/device/testing/$p/APKBUILD" "/work/src/pmaports/$p/APKBUILD"
done

[ "$ACTION" = "setup" ] && { echo "==> setup done"; exit 0; }

# NOTE ON THE PASSWORD: --password is pmbootstrap's documented automation hook and
# is handled in PLAIN TEXT, including in the logfile. It is a throwaway for first
# boot. Change it on the device immediately:  passwd
DUMMY_PASSWORD="${ZEUS_PASSWORD:-147147}"

echo "==> building packages"
"${PMB[@]}" -y build linux-postmarketos-qcom-sm8450-zeus device-xiaomi-zeus

echo "==> installing rootfs"
"${PMB[@]}" -y install --no-fde --password "$DUMMY_PASSWORD"

echo "==> exporting"
mkdir -p /work/out/pmb
"${PMB[@]}" -y export /work/out/pmb
ls -la /work/out/pmb
