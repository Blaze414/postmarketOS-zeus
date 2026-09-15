# Installing postmarketOS on a Xiaomi 12 Pro (zeus)

What a fresh install gives you, what it does not, and the exact steps.

`docs/02-build.md` describes a combined `xiaomi-zeus.img` and a `vbmeta.img`.
Neither is produced any more - the build switched to split images, because a
combined image is a disk image with its own partition table and Linux does not
parse a partition table nested inside a partition, so the initramfs finds no
filesystem at all. Use this page, not that one.

## Before you start

- **The bootloader must already be unlocked.** Unlocking erases the phone,
  needs a Xiaomi account approval wait and `mi-unlock` on Windows, and cannot
  be done from here.
- **Everything on the phone is destroyed.** Android, photos, messages, all of
  it.
- You need `fastboot` on the host. On macOS, `brew install
  android-platform-tools`; Docker cannot pass USB through, so flashing runs on
  the host, not in the build container.
- Recovery is always available: hold Volume-Down + Power to reach fastboot.
  Nothing in this process touches the bootloader itself.

## Build, then flash

```bash
./scripts/dev.sh --priv          # build container
/work/scripts/pmb.sh build       # produces out/pmb/*
```

```bash
./scripts/flash.sh               # from the host, phone in fastboot
```

`flash.sh` checks the phone is in fastboot and unlocked, prints exactly what it
is about to overwrite, and asks you to type `ERASE` before it writes anything.
It then flashes, in order:

| image | partition | why |
|---|---|---|
| `vbmeta-disabled.img` | `vbmeta_a`, `vbmeta_b` | this phone ships `Verity mode: true` and refuses an unsigned kernel outright. Both slots, because the bootloader can fall back to the other one |
| `boot.img` | `boot` | kernel, devicetree and initramfs |
| `xiaomi-zeus-root.img` | `userdata` | the whole system, a bare f2fs labelled `pmOS_root` |

First boot takes a couple of minutes while the filesystem is resized and the
user is created.

### Reflashing only the kernel

```bash
./scripts/flash.sh kernel
```

There is a trap here worth knowing about. `boot.img` carries the filesystem
UUIDs of the rootfs image built beside it, and the initramfs finds root by
UUID. Flash a newly built `boot.img` onto a phone installed from an *earlier*
build and it looks for a filesystem that is not there - the phone lands back in
fastboot, looking exactly like a kernel that failed to boot.

Read the UUIDs off the phone and pass them in:

```bash
cat /proc/cmdline          # on the phone: pmos_root_uuid=..., pmos_boot_uuid=...
```

```bash
ZEUS_ROOT_UUID=<root-uuid> ZEUS_BOOT_UUID=<boot-uuid> ./scripts/flash.sh kernel
```

`scripts/bootimg-uuid.py` does the rewrite; both UUIDs are the same length as
what they replace, so the cmdline is edited in place and nothing else moves.

## Checking an image before you flash it

```bash
/work/scripts/audit-image.sh     # in the build container
```

Every fix this port has accumulated should be in the image, not only on the
phone we happened to iterate on. The audit walks the built rootfs and the boot
image and checks each one - the CPU profile switcher and its conservative
default, the WiFi ASPM and power-save fixes, the ALSA UCM profiles and ADSP
topology, the panel cutout and shell config, the `qbootctl` runlevel link that
stops the bootloader rolling the slot back after about seven boots, the
firmware subpackages, and the devicetree nodes for the panel, speaker TDM pins
and GPR passthrough. It exits non-zero if anything is missing.

## What works

| | |
|---|---|
| Display, touch, on-screen keyboard | yes, with the punch-hole cutout |
| WiFi | yes - PCIe ASPM L1 disabled and WiFi power-save off, which fixes scan-stop and a link-down crash under load |
| CPU | all eight cores, prime up to 2.995 GHz. Conservative profile by default; `zeus-cpu-profile performance` to unlock, `conservative` to go back |
| GPU | hardware accelerated, reaches its 818 MHz stock ceiling |
| Audio - headphones and USB-C | yes |
| Audio - internal speakers | **no**. See `docs/13-sm8450-mainline-findings.html` |
| Modem, camera | not attempted |

## Verified end to end

Run on hardware from fastboot to a booted phone on 2026-09-16, against the
kernel r58 / `#59` build:

| step | result |
|---|---|
| `vbmeta_a`, `vbmeta_b`, `boot`, `userdata` | flashed, 3 GB rootfs sparsed into 3 chunks in 55 s |
| first boot | USB network up ~30 s after reboot, sshd ~160 s |
| identity | cmdline UUIDs match the rootfs image built beside the boot image - no rewrite needed for a fresh install |
| CPU | conservative by default: cpu4 1881600, cpu7 1728000, boost off. `zeus-cpu-profile performance` gives cpu7 2995200 with boost on, `conservative` puts it back |
| WiFi | ASPM policy `[performance]`, `l1_aspm=0`, NetworkManager drop-in present, `wlan0` up |
| audio | card present with both playback devices, `/dev/aud_pasthru_adsp` present |
| A/B slot | `qbootctl` started, so the slot is marked good and the bootloader will not roll back |
| shell | greetd and NetworkManager started, phosh running, DSI connector present |

The pre-flight checks the script relies on were confirmed on the same device:
`unlocked: yes`, `current-slot: a`, and `userdata` (f2fs), `boot`, `vbmeta_a`
and `vbmeta_b` all present.
