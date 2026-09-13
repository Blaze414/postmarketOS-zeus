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

### Next blocker

`make modules` fails:

```
drivers/clk/qcom/clk-debug.o: ./include/trace/define_trace.h:95: fatal error: './trace.h' file not found
```

A missing trace header include path in the vendor clk debug code - a build-system
quirk, not a design problem. After that: build the display-drivers techpack, then
package with Droidian's linux-packaging-snippets using `src/droidian/kernel-info.mk`.
