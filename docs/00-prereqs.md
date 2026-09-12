# 00 — Prerequisites

Do these in order. Step 1 has a multi-week wall-clock delay, so start it today
and do everything else while waiting.

## 1. Bootloader unlock (START NOW — 7 to 30 day timer)

On the phone:
1. Settings → About phone → tap MIUI/HyperOS version 7x → Developer options enabled
2. Developer options → **Mi Unlock status** → Add account and device
3. Sign in with a Mi Account. **This binds the account and starts the waiting period.**

The timer runs whether or not you touch the phone again. Xiaomi has lengthened it
over time (7 days historically, 30+ on recent HyperOS). Nothing below can proceed
without it, so do not defer it.

After the timer expires, on a Windows machine (Mi Unlock Tool is Windows-only):
- Phone into fastboot (power off, hold Vol-Down + Power)
- Run Mi Unlock Tool, sign in with the same account, unlock

**Unlocking wipes the device.** Back up first.

## 2. Back up everything you cannot regenerate

Photos, 2FA seeds, authenticator apps, WhatsApp, anything DRM-bound.
Note that unlocking drops Widevine L1 → Netflix/Prime drop to SD, and
some banking apps will refuse to run. Permanently, on this device.

## 3. Dump the stock device

Run `scripts/dump-stock.sh`. It needs root (Magisk) for the partition dumps —
if you have not rooted, at minimum grab the downstream devicetree, which does not need root:

```bash
adb pull /sys/firmware/fdt zeus-stock.dtb
```

That file is the single most valuable artifact in this whole project. It is the
Xiaomi-authored description of the hardware you are about to re-describe in mainline.

## 4. Host toolchain (macOS note)

**pmbootstrap does not run properly on macOS.** It needs Linux namespaces and
a Linux loop-device setup. You are on darwin, so you need one of:

- A Linux box or VM (UTM/Parallels/VMware, Ubuntu 24.04+, 60GB+ disk)
- A cloud Linux VM
- WSL2 will *not* work reliably either (loop devices / fastboot passthrough)

Do not fight this. Get a real Linux host with USB passthrough for fastboot.

On that host:

```bash
sudo apt install -y git python3 python3-pip android-tools-adb android-tools-fastboot device-tree-compiler
pipx install pmbootstrap
```

## Gate

Do not proceed to `01-devicetree.md` until:

- [ ] Bootloader unlocked (fastboot reports `unlocked: yes`)
- [ ] `zeus-stock.dtb` pulled and decompilable with `dtc`
- [ ] Linux host with working `fastboot devices`
- [ ] You have accepted that camera and fingerprint will not work
