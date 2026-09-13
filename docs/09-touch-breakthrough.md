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

## Solved: the reads were split in two

GENI was never mis-clocking. This driver builds every register read as **two
transfers in one message**:

```c
transfer[0].len = cmdLength;  transfer[0].tx_buf = cmd;     rx_buf = NULL;  /* address */
transfer[1].len = byteToRead; transfer[1].tx_buf = NULL;    rx_buf = outBuf; /* data */
```

A TX-only transfer followed by an RX-only one. `spi_bitbang` walks a message
transfer by transfer with the chip select held low throughout, so the FingerTip
sees one continuous transaction and answers - which is exactly why bitbanging
"worked" and made the chip look healthy while GENI looked broken. GENI does not
reproduce that shape, and the chip returns nothing: hence 0x00 on every read,
never garbage and never partial.

The fix is to stop splitting them. `fts_spi_wr()` flattens any write-then-read
into a **single full duplex transfer**: the command bytes padded out with zeros
to the full length, the reply taken from the tail of the rx buffer. One transfer
per message leaves no inter-transfer behaviour for a controller to get wrong.
Applied to all three paths - `fts_read`, `fts_writeRead` and
`fts_writeThenWriteRead` - as
`0002-fts-single-full-duplex-transfer-for-geni.patch`.

On the real controller, first boot after the patch:

```
FW VER = 0031
Lockdown:0x48,0x38,0x32,0x06,0x4c,0x32,0x31,0x00
Probe Finished!
```

| | bitbang | GENI + patch |
|---|---|---|
| bus | `spi-gpio` (software) | `9c0000.geniqup/990000.spi` (hardware) |
| clock | ~1 MHz, jittery | 12 MHz, matching downstream |
| `F3 12` errors | 22710 | **0** |
| CPU cost | a spinning bitbang loop per transfer | none |

The clock was never the problem either: 12 MHz, the downstream value, works. The
1 MHz in the devicetree was a debugging step that had been left in place.

`/delete-property/ dmas` was reverted - the GPI DMA channels are back, and with
single-transfer reads the DMA path behaves. The earlier observation that FIFO
mode turned a silent timeout into `ERROR_BUS_R` was a real signal, but it was
pointing at the transfer shape rather than at DMA.

The `spi-gpio` twin is left in the devicetree, disabled. It cost one kernel
config change and earned the entire diagnosis; it is worth keeping for the next
time a peripheral looks dead.

## What the Android kernel does that we were not

Comparing the stock devicetree with ours explains both remaining symptoms, and
neither is about the bus.

Stock's touch node carries a pile of properties we had none of:

```
fts,touch-deadzone-filter-ver/-hor        fts,support-vsync-mode
fts,touch-edgezone-filter-ver/-hor        panel = <...>
fts,touch-cornerzone-filter-ver/-hor1/2   fts,touch-follow-performance
```

Two of those confirmed decisions already taken: `fts,irq-flags = <0x2008>` is
exactly the IRQF_ONESHOT value derived earlier, and `spi-max-frequency` on the
touch node is 12 MHz. Stock also marks the SPI controller `qcom,rt`, which
mainline's GENI driver does not parse - worth revisiting if latency bites.

### Mistouches: the firmware was already telling us

The zone filter tables are **not parsed by this driver at all**. Downstream
implements rejection in its separate `xiaomi_touch` layer, which mainline does
not have. But the interesting part is upstream of that:

```c
case TOUCH_TYPE_FINGER:
case TOUCH_TYPE_GLOVE:
case TOUCH_TYPE_PALM:      /* falls through */
	tool = MT_TOOL_FINGER;
```

The firmware classifies palm contacts and reports `TOUCH_TYPE_PALM`, and this
driver forwards them as ordinary fingertips. On curved glass that is a stream of
spurious touches. Rejection is now done in the driver: palms are dropped, as are
contacts starting in the bottom corner boxes, converted from stock's
`fts,touch-cornerzone-filter-ver` into this driver's super-resolution units.
Rejected ids are tracked so their motion is dropped too - the enter handler
doubles as the motion handler - and a contact that turns into a palm after being
reported gets its slot released so it cannot stick down forever.

Stock's 60px left/right edge bands are deliberately **not** applied: downstream
treats them as conditional rather than absolute, and blanket suppression would
eat legitimate edge swipes. `fts,edge-suppress-x` exists to try a band without a
rebuild, defaulting to 0.

### Touch stopping entirely: nothing told the driver the display came back

`resume_bit` gates every touch report:

```c
if (!info->resume_bit)
	goto no_report;
```

It is only cleared and set by `fts_suspend_work` / `fts_resume_work`, and the
only things that queue those are a debugfs helper and system PM. There is no
panel notifier in this fork. So once the display blanked, nothing resumed the
driver and touch stayed dead.

Mainline's equivalent of Xiaomi's notifier is `drm_panel_follower`: the panel
calls its followers around its own prepare/unprepare, and
`drm_panel_add_follower()` resolves the panel through a `panel` phandle on the
follower's own node - the very property stock has on this touchscreen and we did
not. Added, along with `panel = <&zeus_panel>`. The driver now logs
`following panel for display state` at probe.

### Is porting xiaomi_touch itself worth it?

Mostly not. `xiaomi_touch` is a control surface - a misc device and sysfs nodes
through which Android userspace pushes tuning (the zone tables, tap sensitivity,
follow performance) down to the firmware. The rejection logic lives in the
firmware and in Xiaomi's HAL, not in that driver. Porting it without the Android
userspace that drives it would add an API nothing calls. The behaviour worth
having is the rejection itself, which is why it went straight into the report
path instead.
