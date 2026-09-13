# Option A: Droidian (Halium) on the Android kernel

Goal: a usable phone. Touch, WiFi, audio and modem run the vendor drivers on the
vendor kernel, with a Debian userland on top through libhybris.

## Starting position

No Droidian port exists for zeus, cupid, or **any** SM8450 device - the Xiaomi ports
in `droidian-devices` are all SDM6xx/7xx era. This is a fresh port. What we already
have that a cold start would not:

- official LineageOS kernel (5.10.256) and devicetrees, cloned in `/src/downstream`
- boot image geometry **verified by flashing** - offsets, page size, header v2
- the AVB situation understood: zeus reports `Verity mode: true` and needs an empty
  vbmeta on **both** slots
- dtbo/vendor_boot behaviour understood (mainline needed them erased; Halium wants them)
- proprietary firmware already extracted and merged (`scripts/dump-firmware.sh`,
  `scripts/pil-squash.py`)
- a complete hardware inventory (`docs/05-hardware-inventory.md`)
- Android's `super` never touched, so system/vendor/product are intact - Halium needs
  the vendor partition for its HALs

## Package layout Droidian expects

Two repos per device, modelled on `linux-android-xiaomi-lavender`:

| | |
|---|---|
| `linux-android-xiaomi-zeus` | the kernel tree on a `droidian` branch, plus `debian/` packaging and `debian/kernel-info.mk` |
| `adaptation-droidian-zeus` | device adaptation: udev rules, HAL glue, quirks |

`src/droidian/kernel-info.mk` is written with zeus's real values - offsets and header
version verified on hardware, A/B rather than a-only, vbmeta required, fastboot id
`zeus`, CPU `SM8450`.

## Order of work

1. **Restore the Android boot chain.** Halium boots the vendor stack, so `vendor_boot`
   and `dtbo` need to go back - the opposite of what mainline required. Stock images
   are in `~/Downloads` (`boot.img`, `vendor_boot.img`, `dtbo.img`), all verified as
   valid. Confirm Android still boots: that proves `super` is intact.
2. **Build a Halium-compliant kernel.** LineageOS 5.10.256 plus the Halium kconfig
   requirements (`CONFIG_DEVTMPFS=y`, namespaces, USB configfs, etc). Run
   `mer-kernel-check` against the result.
3. **Package it** with Droidian's `linux-packaging-snippets` and the kernel-info.mk here.
4. **halium-boot.img** - kernel plus the Halium generic initramfs.
5. **Droidian rootfs** - the generic arm64 image, flashed to userdata.
6. **Adaptation package** for anything device-specific.

## Honest risks

- **Android 12/13-era Halium is thinner ground** than the Halium 9/10 devices Droidian
  mostly ships. Droidian's docs say Android 9 or above is portable, but the existing
  ports are older hardware.
- msm-kernel 5.10 is a **clang** build with its own toolchain expectations; the Debian
  packaging assumes an Android clang that may need pinning.
- Display, GPU and camera all run through libhybris against Android blobs. That works
  when it works, and debugging it is unlike debugging mainline.
- This discards the mainline work as a running system, though the knowledge and the
  extracted firmware carry over.

## What is already known to work on this device, from the mainline port

Display 1440x3200, Adreno 730 with our extracted firmware, battery via qcom-battmgr,
all three buttons, Bluetooth. Those are not guarantees for Halium, but they do confirm
the hardware and firmware we extracted are good.

## Progress: the downstream kernel builds

`Image.gz`, 15,024,887 bytes, from LineageOS 5.10.256 with clang 19 and `LLVM=1`.
Artifacts in `out/droidian/`.

### Halium kconfig work

`mer-kernel-check` against `gki_defconfig` + `vendor/waipio_GKI.config` reported **23
errors**. `src/droidian/zeus_halium.config` fixes all of them; the saved result is
`src/droidian/zeus_droidian_defconfig` (7674 lines).

Notable entries:

- `CONFIG_STATIC_USERMODEHELPER` must be **off** - systemd cannot work with it on
- `DUMMY`, `INET_AH`, `INET6_AH`, `IP_NF_MATCH_RPFILTER` must be `=y`; `=m` is rejected
- `VT`, `DEVTMPFS`, `DEVTMPFS_MOUNT`, `SYSVIPC`, `FHANDLE` - the usual Android omissions
- the vendor Kconfig for the SPI touch driver declares `depends on I2C`, so I2C must
  stay enabled even though the part is on SPI

One reported error remains, `CONFIG_DUMMY`, and it is a false positive: the config
does contain `CONFIG_DUMMY=y`.

### The touch driver is in-tree here

`TOUCHSCREEN_ST_FTS_V521_SPI` lives at `drivers/input/touchscreen/fts_spi/Kconfig` and
is wired into the parent Makefile. This is the entire reason for taking this path.

### Touch depends on the display techpack

Building it in fails the vmlinux link:

```
ld.lld: error: undefined symbol: panel_event_notifier_register
ld.lld: error: undefined symbol: register_xiaomi_touch_client
```

- `register_xiaomi_touch_client` is in-tree, in `drivers/input/touchscreen/xiaomi/`
  (`CONFIG_TOUCHSCREEN_XIAOMI_TOUCHFEATURE`)
- `panel_event_notifier_*` has only *consumers* in this tree (battery charger, thermal,
  hwmon). The provider is the external **display-drivers** techpack, available in the
  `xiaomi-sm8450-kernel` org.

So on this kernel the touchscreen genuinely depends on the display driver. Both touch
modules are therefore `=m`, which links cleanly and defers the symbol to load time.

### Modules build too - 333 of them

`make modules` initially failed across several vendor directories with

```
include/trace/define_trace.h:95: fatal error: './trace.h' file not found
```

The trace headers are present; the directories just lack `$(src)` on the include
path. Fixed systematically by adding `ccflags-y += -I$(src)` to every Makefile in a
directory shipping a `*trace*.h` - 77 Makefiles in total. Note the glob has to be
`*trace*.h`, not `trace*.h`: `drivers/tty/serial/serial_trace.h` does not match the
narrower one.

Then modpost failed on undefined `get_hw_version_platform` and
`get_hw_country_version`, referenced by the FTS touch driver and by the CNSS/ICNSS
WiFi platform drivers. Provider is `drivers/misc/hwid/hwid.c`, symbol
`CONFIG_MI_HARDWARE_ID`, default n. Enabled.

### Touch does NOT need the display techpack

Worth correcting: `fts_touch_spi.ko` declares `depends: xiaomi_touch,panel_event_notifier`,
and it looked like the notifier would have to come from the external display-drivers
repo. It does not - `drivers/soc/qcom/panel_event_notifier.c` is **in this kernel tree**
and exports both symbols. It builds as `panel_event_notifier.ko` alongside everything
else. The lineage-20 display-drivers techpack does not contain the symbol at all.

Full closure for touch, all three built:

| module | depends on |
|---|---|
| `fts_touch_spi.ko` (2.6 MB) | `xiaomi_touch`, `panel_event_notifier` |
| `xiaomi_touch.ko` (339 KB) | `panel_event_notifier` |
| `panel_event_notifier.ko` (141 KB) | - |

The display techpack is still needed for **display**, but it is off the critical path
for proving touch works.

### Next steps

1. Build the Halium initramfs and assemble `halium-boot.img` using
   `src/droidian/kernel-info.mk`.
2. Restore `vendor_boot` and `dtbo` on the device (stock images verified in
   `~/Downloads`), since Halium boots the vendor stack.
3. Flash and check whether `fts_touch_spi` finds its chip id - the single question
   this whole path exists to answer.

## A flashable boot image exists

`out/droidian/halium-boot.img` - 17,342,464 bytes, `ANDROID!`, header v2, page size
4096, kernel 15,024,887 / ramdisk 1,854,971 / dtb 451,723.

Contents: the downstream 5.10.256 kernel, a minimal diagnostic initramfs, and the
zeus devicetree.

### Devicetree

zeus is an **overlay** on `waipio.dtb`, and the entire `dtbo-y` list sits behind
`CONFIG_BUILD_ARM64_DT_OVERLAY` - without it no `.dtbo` is emitted at all. With that
enabled, `waipio.dtb` (396 KB) and `zeus-sm8450-pm8008-overlay.dtbo` (74 KB) build,
and `fdtoverlay` merges them into `zeus-merged.dtb` (451 KB), which carries the full
vendor `fts@0` node.

Merging rather than relying on the `dtbo` partition is deliberate: that partition is
erased from the mainline work, and a self-contained dtb avoids depending on ABL's
overlay machinery. The merged dtb keeps `qcom,msm-id = <0x1c9 0x10000>`, which is
what ABL matches on.

The display overlay (`zeus-sde-display-mtp-overlay.dtbo`) does **not** apply to this
base - `fdtoverlay` returns `FDT_ERR_NOTFOUND`. It targets a different base dtb. Not
needed to test touch.

### Build fixes needed along the way

| problem | fix |
|---|---|
| `./trace.h file not found` across vendor dirs | `ccflags-y += -I$(src)` in every Makefile shipping a `*trace*.h` (77 of them) |
| `get_hw_version_platform` undefined | `CONFIG_MI_HARDWARE_ID=y` (`drivers/misc/hwid`) |
| `bindings/qcom,audio-ext-clk.h` not found | headers live in the **audio-kernel techpack**, not the devicetrees repo; merged into `scripts/dtc/include-prefixes/bindings` |
| `dt-bindings/msm-camera.h` not found | copied from the camera-kernel techpack |
| diwali/cape dtbs reference missing `.dtbi` | `CONFIG_ARCH_DIWALI`/`CAPE` off - only waipio is wanted |
| no `.dtbo` emitted | `CONFIG_BUILD_ARM64_DT_OVERLAY=y` |

### The diagnostic initramfs

`src/droidian/initramfs/init` is deliberately minimal: busybox, the three touch
modules, USB CDC-ECM at 172.16.42.1 and telnetd. It exists to answer one question -
does `fts_touch_spi` read a real chip id when `xiaomi_touch` and
`panel_event_notifier` are present? On mainline, with both absent, it always read
0x00.

### To actually test it

1. `fastboot flash vendor_boot ~/Downloads/vendor_boot.img` - Halium boots the vendor
   stack, and this partition is currently erased
2. `fastboot flash boot out/droidian/halium-boot.img`
3. vbmeta is already disabled on both slots from the mainline work
4. `telnet 172.16.42.1`, then `dmesg | grep FTS`

This overwrites the working mainline install.

## First flash attempt: dark, no output

`vendor_boot` restored and `halium-boot.img` flashed to `boot_a`, both OK. The device
then reached none of fastboot, adb or USB networking, and the screen stayed dark.

Ruled out immediately: busybox in the initramfs is statically linked, so `/init` had a
working interpreter.

What remains indistinguishable from here:

1. ABL rejected the merged devicetree despite the board-id patch
2. the kernel panicked early
3. the initramfs ran and failed silently (USB gadget never came up)

All three look the same: silence. The mainline port was recovered by re-erasing
`vendor_boot` and reflashing `out/pmb/boot.img`; pmOS came back in 20 seconds with
`userdata` untouched.

## The diagnostic channel we should have used first

zeus's own stock kernel cmdline (from `stock-dump/zeus-stock.dts`) shows Xiaomi routes
oops logs to a partition:

```
block2mtd.block2mtd=/dev/block/sda15,2097152
mtdoops.mtddev=0 mtdoops.record_size=2097152 mtdoops.dump_oops=0
pstore.compress=none printk.always_kmsg_dump=1
```

So a panicking kernel writes its log to **sda15**, which survives a reboot - and we
have a working OS on this device that can read that partition afterwards. Adding those
arguments to the halium-boot cmdline turns a silent failure into a readable one,
without needing a serial cable.

Next attempt should carry them, plus `console=ttyMSM0,115200n8` and `earlycon`.
