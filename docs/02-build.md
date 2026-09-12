# 02 — Build and flash

On the Linux host. Assumes `scripts/setup.sh` has cloned the upstreams.

## Device package

pmbootstrap needs a `device-xiaomi-zeus` package. Derive from cupid's — the file is short
and mostly correct already. Ours lives in `src/device-xiaomi-zeus/`.

Deltas from cupid's `deviceinfo`:

```sh
deviceinfo_name="Xiaomi 12 Pro"
deviceinfo_codename="xiaomi-zeus"
deviceinfo_dtb="qcom/sm8450-xiaomi-zeus"
deviceinfo_screen_width="1440"
deviceinfo_screen_height="3200"
deviceinfo_super_partitions="..."   # read from stock-dump/inventory.txt, do NOT copy cupid's
```

Everything else (flash offsets, header version 2, fastboot method) carries over — same
bootloader generation.

## Build

```bash
pmbootstrap init    # vendor: xiaomi, device: zeus, UI: console for first boot
```

Use **console** UI for the first boot. Not Phosh. A desktop that fails to start looks
identical to a kernel that failed to boot, and you will waste a day on it.

```bash
pmbootstrap build device-xiaomi-zeus
```

```bash
pmbootstrap install --no-fde
```

```bash
pmbootstrap flasher flash_kernel && pmbootstrap flasher flash_rootfs
```

## First boot — what success looks like

No display. That is expected and fine. Success is:

```bash
ssh user@172.16.42.1
```

USB gadget networking comes up before the display does. If you get a shell, the kernel
booted, the dts is structurally valid, and you have won the hardest round.

## If it does not boot

```bash
# the bootloader's own log survives a failed boot
fastboot oem dmesg
```

```bash
# or catch the kernel's last words over USB
pmbootstrap flasher flash_kernel && cat /dev/ttyACM0
```

`PMOS_NO_OUTPUT_REDIRECT` is already in the cmdline (inherited from cupid) — it keeps
early console output going to the framebuffer instead of being swallowed.

---

## Actual working flow (verified 2026-09-12)

On macOS, once:

```bash
./scripts/setup.sh                 # host-side reference clones
./scripts/dev.sh                   # builds + enters the container
```

Inside the container, once:

```bash
./scripts/container-setup.sh       # clones the kernel into the /src volume
```

Then, per change:

```bash
./scripts/build-dtb.sh             # links our sources in, registers the dtb, builds it
```

Output lands in `out/sm8450-xiaomi-zeus.dtb` on the Mac.

### Status

`sm8450-xiaomi-zeus.dtb` builds clean — 108026 bytes. Verified by decompiling the blob:
model `Xiaomi 12 Pro`, compatible `xiaomi,zeus`, panel `mdss,l2-38-0c-0a-dsc`,
`fts,x-max = 0x3840` / `y-max = 0x7d00` (matching the original device dump byte for byte),
remoteproc firmware repointed to `qcom/sm8450/zeus/`.

**This is a syntax and binding check only.** A dtb that compiles says nothing about whether
the hardware description is correct. That is what first boot is for.

### Gotchas hit while getting here

- The qcom dts Makefile separates with a **tab**. A `sed` written against a space silently
  does nothing, and `make qcom/<name>.dtb` still works because an explicit target bypasses
  the list - so the registration looks fine until `make dtbs` quietly skips the device.
  `build-dtb.sh` now asserts the registration landed.
- Docker named volumes are created root-owned; the container runs as `pmos`.
  `container-setup.sh` chowns `/src` on first use.

## Kernel builds (2026-09-12)

`./scripts/build.sh kernel` produces, verified present:

| artifact | size |
|---|---|
| `out/Image.gz` | 10.3 MB |
| `out/sm8450-xiaomi-zeus.dtb` | 108790 bytes (contains our fixed regulators + `pmic@c`) |
| `panel-l2-38-0c-0a-dsc.ko` | 73 KB |
| `qcom-pm8008.ko`, `qcom-pm8008-regulator.ko` | zeus touch avdd path |
| `fts_touch_spi.ko` | touchscreen, inherited from cupid's config |

### Two traps worth remembering

**Never edit a script while the container is running it.** `scripts/build.sh` is
bind-mounted from the Mac, and bash reads a script incrementally by byte offset. Editing it
mid-run shifted the file under the live interpreter, which resumed mid-token and died with
`==> full kernel build: command not found` (exit 127) *after* a perfectly good build. Copy
the script to a frozen path and run that:

```bash
cp scripts/build.sh /tmp/build-frozen.sh
docker run ... -v /tmp/build-frozen.sh:/build.sh:ro zeus-build bash /build.sh kernel
```

**Guard config-fragment edits per symbol, not per block.** The first version keyed the whole
fragment block on `DRM_PANEL_XIAOMI_38_0C_0A`, so once that symbol existed the later PM8008
lines were never appended. The build then failed its own assertion, which is the system
working - but the bug would have been invisible without the assertion.

## Image built (2026-09-12)

```bash
./scripts/dev.sh --priv          # then, inside:
/work/scripts/pmb.sh build
```

Artifacts, copied out of the container volume into `out/pmb/`:

| file | size |
|---|---|
| `boot.img` | 20,074,496 B — valid `ANDROID!` boot image |
| `xiaomi-zeus.img` | 818,260,588 B — full rootfs |
| `sm8450-xiaomi-zeus.dtb` | 108,790 B |

Verified, not assumed:
- `boot.img` starts with the `ANDROID!` magic
- our **exact** 108790-byte dtb is embedded in `boot.img` at offset 10317424, immediately
  after the 10313328-byte kernel — consistent with `deviceinfo_append_dtb="true"`
- the dtb is byte-identical to the one validated by hand, so the panel regulators, the
  pm8008j node and the zeus touch parameters are all in the image

### Four failures on the way here, in order

1. **exit 137 at the kernel compile.** SIGKILL = OOM. The Docker VM was on defaults
   (2 CPUs / 1.9 GB). Raised to 10 CPUs / 16 GB.
2. **`error 127` at `GENHDR .../a2xx.xml.h`.** `/bin/sh: python3: not found` — the msm DRM
   driver generates its register headers with `registers/gen_header.py`, and the Alpine
   buildroot only installs declared `makedepends`. The stock sm8450 package does not declare
   python3 because its 2023 pin predates that generator existing.
3. **`mkinitfs: only one kernel release/flavor is supported, found: []`.** Our `package()`
   was missing `usr/share/kernel/$_flavor/kernel.release`, which is how mkinitfs discovers
   flavors. Dropped because the stock APKBUILD was read truncated and its `package()`
   looked complete.
4. **The same mkinitfs error again, after the fix.** abuild caches on
   `pkgname-pkgver-pkgrel` and does not hash file contents, so editing an APKBUILD without
   bumping `pkgrel` silently reuses the stale apk. The tell was the timing: it failed in
   under a minute when a kernel build takes six. `pmb.sh` now passes `--force`.

## Flashing

**Not yet attempted.** The device must be in fastboot (power off, hold Vol-Down + Power).

```bash
fastboot flash boot out/pmb/boot.img
```

```bash
fastboot flash userdata out/pmb/xiaomi-zeus.img
```

```bash
fastboot reboot
```

### What success looks like

**A black screen and a working SSH login.** USB gadget networking comes up before the
display does:

```bash
ssh user@172.16.42.1
```

Password is whatever `ZEUS_PASSWORD` was at build time (default `147147`). **Change it
immediately with `passwd`** - pmbootstrap's `--password` is handled in plain text and is
written to the build log.

Do not judge the port by whether the screen lights up. Stage 0 is a shell.

### Known non-working on this image

GPU, WiFi, modem and DSP: the `firmware-xiaomi-zeus-*` packages do not exist upstream, so
no firmware is installed. Camera and fingerprint: no mainline support at all.

## Final image (2026-09-13) — Phosh, touch, device optimizations

```bash
./scripts/dev.sh --priv        # then inside:
/work/scripts/pmb.sh build     # or `install` to skip the package rebuild
```

| artifact | |
|---|---|
| `out/pmb/boot.img` | 20,152,320 B, `ANDROID!`, our dtb embedded |
| `out/pmb/xiaomi-zeus.img` | 2.37 GB Android sparse image |

Verified in the built rootfs: `st_fts_l1.ftb` + `stm_fts_production_limits.csv` in
`/lib/firmware`, `/etc/phosh/phoc.ini` with `scale = 3`, `qbootctl` and
`postmarketos-ui-phosh` installed.

### Do NOT use --split on this device

`--split` emits bare ext2/ext4 filesystem images (`pmOS_boot`, `pmOS_root`) meant for
devices that have two real partitions to hold them. zeus has no spare partition for
`pmOS_boot`. The combined image is self-describing: it carries its own partition table with
both filesystems inside, and the boot.img cmdline finds them by UUID:

```
pmos_boot_uuid=7424ab74-... pmos_root_uuid=935481f0-...
```

Those UUIDs match the two filesystems inside the combined image. Flashing split images here
would leave the initramfs unable to find either.

### Flashing

```bash
fastboot flash boot out/pmb/boot.img
```

```bash
fastboot flash userdata out/pmb/xiaomi-zeus.img
```

```bash
fastboot reboot
```

If it does not boot with AVB enabled, disable verification and retry:

```bash
fastboot --disable-verity --disable-verification flash vbmeta out/pmb/vbmeta.img
```

### Device-specific tuning applied

| | why |
|---|---|
| `phoc.ini` `scale = 3` | 1440x3200 on 70x156mm is 523 DPI; unscaled Phosh is unusable. 480x1066 logical. Integer scale avoids fractional-scaling blur and the extra compositor pass |
| `$pkgname-openrc` declared in `subpackages` | cupid defines `openrc()` but never lists it, so abuild silently skips it. It pulls `qbootctl-openrc`, which marks the A/B slot as successfully booted - without it the bootloader eventually rolls back to the other slot |
| f2fs root | UFS 3.1 flash; log-structured with flash-aware GC. `CONFIG_F2FS_FS=y` already present |

Skipped deliberately: **zram** (the device has 11.4 GB RAM, compression is pure overhead) and
**120 Hz** (the panel does 24/30/40/60/90/120 LTPO but we are fixed at 60 - change the pixel
clock only after the panel has been seen to work at all).
