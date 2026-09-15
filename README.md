# zeus-mainline — postmarketOS on the Xiaomi 12 Pro

Mainline Linux on the Xiaomi 12 Pro (`zeus`, Snapdragon 8 Gen 1 / SM8450), running
postmarketOS with Phosh. Not Ubuntu Touch, and no libhybris: this is a real mainline
port, derived from the existing `cupid` (Xiaomi 12) port and then reworked for the
parts where the two phones differ.

It boots, it is installable from fastboot, and it is usable day to day apart from the
gaps listed below.

## Status

| | |
|---|---|
| Display, touch, on-screen keyboard | works, with the punch-hole cutout |
| GPU | hardware accelerated, reaches the 818 MHz stock ceiling |
| CPU | all eight cores; conservative profile by default, prime up to 2.995 GHz on demand |
| WiFi | works — needs PCIe ASPM L1 disabled and WiFi power-save off |
| Bluetooth | works |
| Audio — headphones, USB-C | works |
| Audio — internal speakers | **no** — see `docs/13-sm8450-mainline-findings.html` |
| Modem, camera, fingerprint | not supported |
| Fast charging | no |

Verified end to end on hardware: flash from fastboot to a booted phone, every fix
present on a fresh install.

## Install

Read `docs/14-install.md`. Short version, with the phone in fastboot and the
bootloader already unlocked:

```bash
./scripts/dev.sh --priv          # Linux build container
```

```bash
/work/scripts/pmb.sh build       # inside the container, produces out/pmb/*
```

```bash
./scripts/flash.sh               # on the host
```

This erases the phone. `flash.sh` prints what it is about to overwrite and makes you
type `ERASE` first. Recovery is always available — Volume-Down + Power reaches
fastboot, and nothing here touches the bootloader.

## What this port had to solve

The deltas against `cupid` are where the work went:

- **Panel.** 1440x3200 LTPO curved Samsung panel with its own DSI and DSC config,
  driven by a generated driver (`src/panel/`) rather than cupid's.
- **Touch.** Different controller and firmware.
- **WiFi stability.** The WCN6855 dropped its link under load until PCIe ASPM L1 and
  WiFi power-save were both turned off.
- **CPU.** The stock frequency tables need unlocking, but the prime core is unstable at
  its ceiling without care, hence the conservative default and the profile switcher.
- **Audio.** A working headphone and USB-C path, an ALSA UCM profile, and an ADSP
  topology. The internal speakers remain unsolved: the TDM endpoint starts but never
  pulls data. That investigation, including a userspace AudioReach/GSL port and a GPR
  passthrough device, is written up for upstream in
  `docs/13-sm8450-mainline-findings.html`.

## Layout

```
docs/     numbered, in the order the work happened; 14-install.md is the user guide
src/      devicetree, panel driver, pmaports packages, kernel shim, ALSA topology
scripts/  build, flash, audit, device access, and the audio diagnostic tooling
docker/   Linux build container, since pmbootstrap does not run on macOS
patches/  out-of-tree patches carried on top of upstream
upstream/ clones of pmaports and friends (scripts/setup.sh fetches these)
```

Useful entry points:

- `scripts/pmb.sh build` — the whole build
- `scripts/flash.sh` — install, or `flash.sh kernel` to reflash boot only
- `scripts/audit-image.sh` — checks a built image carries every fix this port has
  accumulated, so a fresh install is not missing something the development phone had
- `scripts/zeus-ssh.sh` — SSH over the USB network to the running phone

## Notes

`docs/02-build.md`'s flashing section is stale: it describes a combined image and a
`vbmeta.img`, neither of which is built any more. Use `docs/14-install.md`.
