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
