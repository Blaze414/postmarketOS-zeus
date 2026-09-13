# Touchscreen: what is known, and what is not

Status: **not working.** The ST FingerTip controller on spi0.0 answers every
register read with 0x00, so the driver cannot read its chip id and aborts:

```
[ FTS ] chip_id0:0x0,chip_id1:0x0
[ FTS ] read chip error,no panel
[ FTS ] Cannot initialize the device ERROR 80000006
[ FTS ] Probe Failed!
```

## Verified on hardware, not assumed

| | evidence |
|---|---|
| SPI pins muxed | `pin 16..19: 990000.spi function qup4` in `pinmux-pins` |
| Touch GPIOs claimed | during probe: `pin 20/21: spi0.0 f100000.pinctrl:571/572 function gpio` |
| GPIO numbering correct | `gpiochip6: GPIOs 551-761` on the tlmm, so 571 == pin 20 |
| avdd powered | `vreg_l3j state=enabled uV=3304000` |
| vdd powered | `pm8350c_l2 state=enabled uV=1800000` |
| driver reaches the bus | `ZEUSDBG writeRead: cmdLength=5 byteToRead=3` then `spi_sync ret=0` |
| controller reports success | `errors=0 timedout=0` on the spi master |
| dts matches downstream | node properties, pinctrl contents, reset/irq GPIOs, tp-vendor 0x38 |
| driver source is faithful | matches xiaomi-sm8450-kernel downstream, including the `delay_usecs` -> `spi_delay` conversion |

## Hypotheses tested and disproven

1. **Power sequencing.** Both rails forced always-on and measured enabled. No change.
2. **SPI clock too high.** Dropped 12 MHz -> 1 MHz, confirmed `0xf4240` in the dtb. No change.
3. **pm8008 not supplying avdd.** Fixed for real (reset-gpios, IRQ made optional,
   ldo3 voltage snapped to the 8000uV step grid) and `vreg_l3j` now registers and
   enables. Touch unchanged.
4. **`SPI4_WIRE` not defined.** It is defined, in both trees.
5. **`ret` initialised such that the retry loop never runs.** It is `-1`; the loop runs.
6. **`tp_pm_suspend` early return.** Never logged.
7. **Zero-length reads.** Instrumentation shows `byteToRead=3` and `=9`, not zero.
8. **GENI not doing rx-only transfers.** Patched all three read paths to full duplex
   with a zeroed tx buffer (`0003-*.patch`). Confirmed present in the built module
   (`fts_dummy_tx_buf`). No change - reads still return 0x00.

## A measurement that misled me

`/sys/class/spi_master/spi0/statistics` reports `bytes_rx = 0` and
`bytes == bytes_tx` on every probe, and the transfer-size histogram shows no
bucket matching the read length. I read that as "the read transfer never reaches
the wire" and built a theory on it. After patching the reads to full duplex - so
they unambiguously carry both buffers - `bytes_rx` was **still** 0. The counters
therefore do not reflect what this controller actually does, and no conclusion
should be drawn from them. Recorded here so the next person does not repeat it.

## What is genuinely unknown

Whether CLK/MOSI toggle on the wire, and whether MISO is being driven at all.
`spi_sync()` returning 0 only means the controller finished its work; it says
nothing about the device. Distinguishing "chip is mute" from "controller is not
clocking" needs a logic analyser on gpio16-19, or someone who already knows
whether touch works on cupid with this fork.

## Suggested next steps

1. Ask upstream (`sm8450-mainline`) whether the FTS touchscreen works on cupid.
   If it does not, this is a fork-wide gap and nothing in this devicetree fixes it.
2. Scope gpio16-19 during probe.
3. Try holding reset high for longer before the first read - the driver reads
   ~10ms after release, and the downstream stack may sequence this differently.

The two patches here are kept for reference and are **not** in the build:
`0002` adds logging to the read path, `0003` makes reads full duplex.
