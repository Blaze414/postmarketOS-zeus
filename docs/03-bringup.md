# 03 — Bring-up order

Strict order. Each stage assumes the previous one works. Skipping ahead means debugging
two unknowns at once, which is how ports die.

## Stage 0 — shell over USB
Kernel boots, USB gadget net up, ssh to 172.16.42.1.
**Nothing else matters until this passes.**

## Stage 1 — display
Panel driver + DSI timings + regulators. See `01-devicetree.md`.
Check: `cat /sys/class/drm/*/status`, backlight responds, console renders.

## Stage 2 — touch
Check: `evtest` shows coordinates matching where you press.
Watch for inverted axes — common when a template's panel rotation is wrong.

## Stage 3 — GPU
Adreno 730 via freedreno. Mostly inherited from cupid, should be near-free.
Check: `eglinfo | grep -i renderer` says freedreno, not llvmpipe.
Then switch pmbootstrap UI from console to Phosh.

## Stage 4 — WiFi / Bluetooth
WCN6855, same as cupid. Needs firmware blobs from `firmware-xiaomi-zeus`.
Check: `ip link` shows wlan0, `nmcli dev wifi` scans.

## Stage 5 — audio
Qualcomm audio on mainline needs an ALSA UCM profile. cupid's is a starting point;
speaker/earpiece routing will differ.
Check: `speaker-test -c2`, then a call-path test once modem works.

## Stage 6 — sensors
IIO drivers for accel/gyro/light/proximity. Proximity matters — without it the screen
stays on during calls.

## Stage 7 — modem (the gamble)
This is where SM8450 mainline ports usually stall.

Path: `qrtr` + `rmtfs` + `pd-mapper` running in userspace, ModemManager on top,
modem firmware loaded from the dumped `modem.img`.

Check, in order:
```bash
sudo rmtfs -r -P -s        # must stay running, not exit
mmcli -L                   # modem enumerated at all?
mmcli -m 0                 # registered on network?
```

Realistic: data may work, voice calls (VoLTE) probably will not. VoLTE needs an IMS
stack that mainline does not have a good story for. Plan for a data-only device.

## Never going to work
- **Camera** — Qualcomm CamX/ISP is unported on mainline for SM8450. Not "hard", unported.
- **Ultrasonic fingerprint** — no mainline driver, no reverse-engineering effort to join.
- **120W charging** — charge-pump ICs are vendor-specific. Expect ~10-18W USB-PD at best.

Accept these at the start. Every port that fails, fails because someone kept trying to
make the camera work instead of shipping a phone that boots.
