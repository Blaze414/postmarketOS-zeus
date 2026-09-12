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
