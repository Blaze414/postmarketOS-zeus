# Touch: the controller was the problem, not the chip

For the whole port the ST FingerTip controller answered every SPI read with
0x00. `docs/touch-investigation/README.md` lists eleven hypotheses tested and
disproven, and concludes that separating "the chip is mute" from "the controller
is not clocking" needs a logic analyser.

It does not. There is a software equivalent, and the answer is the second one.

## The experiment

`spi-gpio` drives CLK/MOSI/CS as plain GPIOs and samples MISO in software, so it
bypasses the GENI controller completely. Same chip, same four pins, same driver,
different controller - a clean A/B where the only variable is the thing under
suspicion.

`CONFIG_SPI_GPIO=m` and `CONFIG_SPI_BITBANG=m` go in the **packaged** config, not
the tree fragment `scripts/build.sh` edits - that distinction has bitten this
project before. The devicetree carries both buses, the bitbanged twin disabled by
default, and `scripts/select-spi.py` flips a **built** dtb between them so
switching costs a splice rather than a kernel rebuild. Exactly one may be
enabled: they claim the same pins.

## The result

On the bitbanged bus, on the very first try:

```
READ EVENT =03 00 00 00 00 00 00 00
System reset DONE!
readSysInfo: Reading System Info...
FW VER = 0031
Lockdown:0x48,0x38,0x32,0x06,0x4c,0x32,0x31,0x00
parseBinFile: Fw Signature OK!
setScanMode: Setting scan mode OK!
Probe Finished!
```

The chip was never mute. It reads its system info, reports firmware version
0031, returns its lockdown code, passes every CRC check and completes probe.
`mainline's GENI SPI controller does not produce the transaction this chip
expects` is now a measured fact rather than a suspicion.

Touching the screen raises interrupts: the count on `msmgpio 21` went from 1 to
562 across one 25-second window of touching, and stayed flat when untouched.

## Two bugs fixed on the way

**`Failed to init pinctrl`.** The bitbanged twin needs `pinctrl-names` /
`pinctrl-0` / `pinctrl-1` like the original. Both states cover only gpio20/21
(reset and irq), so they do not touch the four bus pins.

**`genirq: Threaded irq requested with handler=NULL and !ONESHOT`.** The driver
passes NULL as the primary handler, which the kernel only allows with
`IRQF_ONESHOT`. `fts,irq-flags` goes straight into `request_threaded_irq`, and
`IRQ_TYPE_LEVEL_LOW` is `IRQF_TRIGGER_LOW` (0x8), so `0x2008` is that flag plus
`IRQF_ONESHOT` - a devicetree fix, no driver patch, no module rebuild. Applied to
both nodes.

## What is still broken

Touches produce no input events. Instead the chip emits, every ~50 ms while
being touched:

```
fts_error_event_handler Received event F3 12 00 00 00 00 00 00
```

`0xF3` is `EVT_ID_ERROR`. `0x12` is **not** in the error table in
`fts_lib/ftsSoftware.h` - it sits between `EVT_TYPE_ERROR_WATCHDOG` (0x06) and
`EVT_TYPE_ERROR_CRC_CFG_HEAD` (0x20), both undocumented in this tree.

Two leads, untested:

1. At probe the chip reports `Mutual negative detect Force cal`. The driver only
   logs the force-calibration status events, it never acts on one. If the
   firmware is waiting to be calibrated, every scan would error.
2. The driver has no panel notifier on mainline (`panel_event_notifier` does not
   exist here), so the controller may never be told the display state in the way
   its firmware expects.

## Where this leaves the port

The bitbanged bus is a diagnostic, not a destination - it burns CPU and is far
slower than the hardware controller. The real fix is now well-posed and narrow:
make GENI produce what this chip wants. That is a much better place to be than
eleven disproven hypotheses about a chip that turned out to be healthy all along.

## Follow-up: what the bitbanged bus actually behaves like in use

With the bitbanged bus in a real session: **scrolling works**, taps mostly do
not register, ghost touches happen, and the display tears while scrolling.

Those are one symptom, not three. spi-gpio can be preempted in the middle of a
transfer, which stretches the CS-low window past what the controller tolerates;
it aborts the transaction and raises an error. The result is a touch stream with
holes in it. Motion survives that - hence working scroll - but a tap needs a
clean down/up pair, and a lost "leave point" leaves a finger logically down
forever, so the tap never becomes a click. The `F3 12` flood at ~50 ms is the
chip complaining about exactly these aborted transactions.

Bitbang proved the chip is healthy. It cannot be the production bus.

### Two display theories tested and dropped

**Log spam causing the tearing.** Console loglevel is 1, so the error flood never
reaches a console, and ~20 printk/s to the ring buffer is nowhere near enough to
stall a compositor.

**The panel being driven as video mode.** The stock cmdline names the panel
`qcom,mdss_dsi_l2_38_0c_0a_dsc_cmd`, so it is command mode, and a command-mode
panel driven as video mode would tear exactly like this. It is not: the panel
driver sets `MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM` and never
`MIPI_DSI_MODE_VIDEO`. TE is wired correctly too - `te-gpios = <&tlmm 86>`
matches stock's `qcom,platform-te-gpio` (0x56 = 86), and pin 86 is live as
`function mdp_vsync` claimed by `ae94000.dsi.0`.

### GENI: forcing FIFO mode changes the failure

Every GENI read returned exactly 0x00 - never garbage, never partial - which is
what a read whose RX is never captured looks like. sm8450's `spi4` declares GPI
DMA channels, so deleting `dmas`/`dma-names` forces the FIFO path.

It changes the failure, which means the DMA path is implicated:

| Path | `fts_system_reset` |
|---|---|
| GENI with GPI DMA | `0x80000007` ERROR_TIMEOUT - reads silently return 0x00 |
| GENI FIFO only | `0x80000002` ERROR_BUS_R - the read **fails outright** |

An explicit bus error is far easier to chase than silent zeros, and it says the
transfer is being rejected rather than quietly producing nothing. No GENI message
accompanies it, so the next step is instrumenting `spi-geni-qcom.c` to see what
`spi_sync` is actually returning and on which transfer shape.

The device is left on the bitbanged bus, since that is the only configuration
where touch works at all.
