# zeus-mainline — postmarketOS on Xiaomi 12 Pro (SM8450)

Target: **mainline Linux / postmarketOS** on Xiaomi 12 Pro (`zeus`, Snapdragon 8 Gen 1 / SM8450).

Not Ubuntu Touch. UT's Halium path caps at Halium 13 (Android 13 / LineageOS 20) and would
mean Android drivers under libhybris. This repo takes the mainline path instead.

## Upstream reality check (verified 2026-09-12)

| Thing | Status |
|---|---|
| SM8450 mainline SoC support | Good. Day-1 Linaro patches; `sm8450.dtsi` upstream |
| Reference port, same SoC | Galaxy Tab S8+ — display w/ DSC @120Hz, Adreno/freedreno, WiFi, BT, touch, UFS root |
| Sibling port, same phone family | **`cupid` (Xiaomi 12) is ported** — `device-xiaomi-cupid` + `sm8450-xiaomi-cupid.dts` (1283 lines), `gpu_accelerated=true` |
| `zeus` devicetree | **Does not exist.** No `sm8450-xiaomi-zeus.dts` |
| `zeus` pmaports package | **Does not exist.** No `device-xiaomi-zeus` |
| `zeus` firmware blobs | Exists: `sm8450-mainline/firmware-xiaomi-zeus` (last pushed 2024-09) |
| Stock dump from real device | ✓ done 2026-09-12 — see `docs/04-hardware-findings.md` |

**So the job is: derive `zeus` from `cupid`.** Same SoC, same PMIC, same era, same vendor.
That is a far smaller job than a bring-up from zero — but it is not zero.

## What actually differs zeus vs cupid

These are the deltas you will be writing code for:

- **Display panel.** cupid = 1080x2400 flat. zeus = 1440x3200 LTPO, curved, different Samsung panel + different DSI controller config and DSC params. Biggest single task.
- **Touch controller.** Different part, different firmware.
- **Charging.** zeus = 120W dual-cell w/ Xiaomi charge-pump ICs. Expect slow charging only, long-term.
- **Cameras.** Not supported on mainline for either. Do not plan around this.
- **Fingerprint.** Ultrasonic. No mainline driver. Will not work.
- **Modem.** The real gamble — see docs/03-bringup.md.

## Honest outcome forecast

Realistic end state: booting phone, working display + GPU + touch + WiFi + BT + audio,
usable Phosh/Plasma Mobile desktop. Calls/SMS: maybe. Camera: no. Fingerprint: no.
Fast charging: no.

If that is not acceptable, stop here and go back to Rung 1 (Termux/proot).

## Layout

- `docs/00-prereqs.md` — bootloader unlock, stock dumps. **Start here, the unlock timer is the long pole.**
- `docs/01-devicetree.md` — deriving `sm8450-xiaomi-zeus.dts` from cupid
- `docs/02-build.md` — pmbootstrap build + flash
- `docs/03-bringup.md` — ordered bring-up checklist, one verification per stage
- `docs/04-hardware-findings.md` — **what the stock dump actually told us** (panel, touch, partitions)
- `docker/` + `scripts/dev.sh` — Linux build container, since pmbootstrap can't run on macOS
- `scripts/setup.sh` — clone upstreams
- `scripts/dump-stock.sh` — pull what you need off the stock device before wiping it
- `src/` — our zeus dts + pmaports device package
