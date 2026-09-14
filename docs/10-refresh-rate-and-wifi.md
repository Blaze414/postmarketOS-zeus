# 120 Hz, the bottom-of-screen artifact, and where WiFi stands

## 120 Hz

Stock lists eight timings for this panel - 120, 90, 60, 40, 30, 24, 10 and 1 Hz -
and **every one of them carries identical porches and the same
`qcom,mdss-dsi-panel-clockrate` of 0x510ff400 (1.36 GHz)**. Only
`qcom,mdss-dsi-panel-framerate` differs. The DSI link is sized once, for the
fastest mode, and simply idles at the slower ones.

Our panel driver declared a single 60 Hz mode, so mainline derived the link from
that - roughly half what the panel is built for.

That matters beyond the refresh rate. This is a command mode panel: the frame is
shifted out on our schedule and the panel latches it against TE. At half the
link rate each frame takes twice as long to transfer, so it can overrun the TE
window, and what gets corrupted is the *tail* of the frame - the bottom of the
screen - and only while something is moving. That is exactly the brief
multi-coloured horizontal bar seen at the bottom during the unlock swipe.

Both modes are now declared from one macro, 120 Hz first and marked preferred.
`/sys/class/drm/*/modes` lists two entries where it previously listed one.

The DSC configuration was checked against stock at the same time and needed no
change: slice 720x50, 8 bpp, 10 bpc, block prediction enabled, two slices per
line - all already matching.

## WiFi: one real fix, one remaining blocker

### Fixed: two supplies were never being voted for

`pwrseq-qcom-wcn` requires ten supplies for a wcn6855, and our devicetree
provided eight:

```
pwrseq-qcom_wcn wcn6855-pmu: supply vddpmumx not found, using dummy regulator
pwrseq-qcom_wcn wcn6855-pmu: supply vddpmucx not found, using dummy regulator
```

cupid does not set them either. The mapping comes from **sm8450-hdk**, the
reference board for this SoC: `vddpmumx-supply = <&vreg_s2e_0p85>` and
`vddpmucx-supply = <&vreg_s11b_0p95>`, which resolve through the `qcom,pmic-id`
letters to pmr735a smps2 and pm8350 smps11 - both regulators this devicetree
already references for other rails. Added; the warnings are gone.

### Remaining: the endpoint is powered after the link is trained

It did not bring the link up. The picture now:

| | |
|---|---|
| `wcn6855-pmu` | probes, owns gpio80 |
| Bluetooth | **works** - `hci0: setting up wcn6855`, so the chip is powered and alive |
| `pci-pwrctrl-pwrseq` | bound to `1c00000.pcie:pcie@0:wifi@0` |
| PCIe | `Phy link never came up` at 1.355 s |
| enumeration | root port `0000:00:00.0` only, no endpoint |

Bluetooth working is the useful part: the PMU rails and the chip itself are fine.
Only the PCIe side fails, and it fails early - the host controller trains the link
about a second into boot and gives up, and nothing retrains it afterwards. A
later `echo 1 > /sys/bus/pci/rescan` finds nothing, and the host driver sets
`suppress_bind_attrs`, so it cannot be unbound and re-probed by hand to test the
ordering directly.

That points at power-up ordering rather than anything in this devicetree: the
`pci-pwrctrl` device exists and is bound, but the endpoint is not up at the
moment the controller trains. The next step is to find out whether the link
trains at all once power is applied - which needs either a host driver that
defers to the pwrctrl, or a way to force retraining - and to check whether WiFi
works on cupid with this same fork, since our WiFi and PCIe nodes are byte for
byte identical to it.

## Sound: there was no sound card at all

`/sys/class/sound/` contained only `timer`. The failure was early and total:

```
qcom-apm gprsvc:service:2:1: Direct firmware load for qcom/sm8450/Xiaomi-12-tplg.bin failed with error -2
qcom-apm gprsvc:service:2:1: tplg firmware loading qcom/sm8450/Xiaomi-12-tplg.bin failed -2
snd-sc8280xp sound: ASoC: failed to instantiate card -2
```

`audioreach_tplg_init()` builds the topology filename from the card itself:

```c
kasprintf(GFP_KERNEL, "qcom/%s/%s-tplg.bin", card->driver_name, card->name);
```

`card->name` comes from the devicetree `model` property, which is `"Xiaomi-12"`,
so it asks for `qcom/sm8450/Xiaomi-12-tplg.bin`. linux-firmware ships exactly one
topology for this SoC, `SM8450-HDK-tplg.bin.zst`, and nothing for any phone. With
no topology the APM component cannot probe, and without it the entire card is
torn down - which is why nothing at all appeared, not merely a missing output.

The HDK is the reference board for this SoC and the audioreach topology describes
ADSP graphs, which are SoC-level rather than board-level, so pointing zeus at it
brings the card up. `card0` now exists with two playback and two capture PCMs and
a headset jack, `wcd938x` binds, and all four CS35L41 speaker amps probe.

This is a workaround, not a finished port. Board-specific routing still needs a
zeus topology, and the `audio-routing` property in the devicetree - the whole mic
matrix - is still commented out.

## Bluetooth: the controller had no address

`hci0` existed, `QCA setup on UART is completed`, rfkill unblocked, `bluetoothd`
running - and `bluetoothctl` still said **"No default controller available"**.
The giveaway was sysfs: `/sys/class/bluetooth/hci0/` had no `address` attribute
at all. The controller was registered as *unconfigured*, so BlueZ would not adopt
it.

QCA parts take their address from `local-bd-address` in the devicetree. Neither
our node nor cupid's set it, so the firmware came up with nothing usable.

This device's factory MAC lives in its own `persist` partition:

```
/persist/qca6490/wlan_mac.bin  ->  wlan0=4ce0db31f3d8
```

Qualcomm gives Bluetooth the next address along, and the property is little
endian, so `local-bd-address = [ d9 f3 31 db e0 4c ]` reads back as
4C:E0:DB:31:F3:D9. `bluetoothctl show` now reports a powered controller named
"Xiaomi 12 Pro".

## Does WiFi work on cupid with this fork?

Not established. The postmarketOS wiki page for xiaomi-cupid is behind Anubis and
would not serve to an automated fetch, and neither the kernel fork nor the
pmaports fork carries a support matrix. What the sources do show:

* cupid's device package depends on `linux-firmware-ath11k`, so WiFi is at least
  intended to work there.
* Our WiFi, PCIe and Bluetooth nodes are byte for byte identical to cupid's -
  including the two omissions found here, `vddpmumx`/`vddpmucx` and
  `local-bd-address`. Bluetooth demonstrably did **not** work as shipped for
  either device, which is some evidence that these nodes were written from a
  template rather than validated on hardware.
* The PHY tables for `qcom,sm8450-qmp-gen3x1-pcie-phy` are present in the kernel,
  so the PCIe PHY itself is supported.

Worth noting from the search: SM8450's PCIe0 PHY initialisation is documented as
differing significantly from other Qualcomm SoCs, and there is recent upstream
work on PCIe0 PHY support for SM8475, the binned variant of this SoC. That is the
area to look at next, along with making the host controller defer to the
pwrctrl device rather than training the link before the endpoint is powered.

## Audio: the card is real, the topology is not ours

With the topology linked the card registers, but playback fails:

```
MultiMedia1 Playback: ASoC: no backend DAIs enabled for MultiMedia1 Playback,
    possibly missing ALSA mixer-based routing or UCM profile
qcom-apm gprsvc:service:2:1: CMD timeout for [1001021] opcode
```

Two separate problems, and the second is the hard one.

**Routing.** On a Qualcomm ADSP card the frontend is not wired to a backend by the
devicetree - that link is a runtime mixer control, normally set by a UCM profile,
and no UCM profile exists for this card. `RX_CODEC_DMA_RX_0 Audio Mixer
MultiMedia1` is the control, and setting it does connect the path. The
devicetree's `audio-routing` was also entirely commented out, so DAPM had no
route from the codec DAIs to anything physical; it is now populated with the
names sm8450-hdk uses for the same wcd938x and the same lpass macros.

**The topology has no TDM.** Listing every backend mixer the loaded topology
provides gives exactly three:

```
PRIMARY_MI2S_RX     RX_CODEC_DMA_RX_0     WSA_CODEC_DMA_RX_0
```

and `amixer controls | grep -ci tdm` returns **0**. Zeus drives its four CS35L41
amps from `TERTIARY_TDM_RX_0`. That backend does not exist in the HDK topology,
so the ADSP has no graph that reaches the speakers and no devicetree change can
create one. The HDK is a development board with WSA speakers; its topology was
never going to carry a phone's TDM amp path.

The APM command timeout on top of that says the ADSP is not accepting these
graphs at all - zeus runs its own `adsp.mbn`, and the HDK topology was built
against the HDK's firmware.

**Speaker audio needs a zeus topology.** The HDK file was a reasonable way to get
the card to exist and it did that, but it cannot be the destination.

## WiFi: what has been eliminated

| Checked | Result |
|---|---|
| `vddpmumx` / `vddpmucx` supplies | were missing, **now fixed**, warnings gone |
| PHY driver support | `sm8450_qmp_gen3x1_pcie` init tables present |
| PERST / WAKE gpios | sm8450.dtsi has gpio94/96, matching stock exactly |
| Link speed | capped at gen2 as sm8450-hdk does - no change |
| `pci-pwrctrl-pwrseq` | bound to `1c00000.pcie:pcie@0:wifi@0` |
| ath11k firmware | WCN6855 present in linux-firmware |
| GPIO numbers | 80/81 match stock's `wlan-en-gpio` / `bt-en-gpio` |

Forcing a link retrain by setting the Retrain Link bit in the root port's Link
Control register, long after boot with everything powered, changes nothing:

```
before: link status 0x1011  speed=1 width=1 active=False
after:  link status 0x1011  speed=1 width=1 active=False
```

`active=False` is Data Link Layer Link Active staying clear. The endpoint is not
answering at all, which also weakens the earlier ordering theory - if it were
purely a question of powering the chip before training, a retrain now would
succeed.

Bluetooth working proves the PMU rails and the chip itself are fine, so what is
left is specific to the WLAN side: whether the pwrseq's wlan target actually
asserts gpio80, and whether this fork's PCIe0 support for sm8450 is complete.
Recent upstream work on PCIe0 PHY for SM8475, the binned variant of this SoC, is
the thread to pull.

## WiFi: the wlan enable line, and why the link still will not train

**gpio80 is asserted.** Reading it directly settles the open question:

```
gpio80  : out high func0 10mA pull up      <- wlan-enable
gpio81  : out high func0 2mA pull down     <- bt-enable
gpio94  : out high func0 2mA pull down     <- PERST#, active low, so released
```

The clocks are all running too - `gcc_pcie_0_clkref_en` enabled with the phy as
its consumer, aux at 19.2 MHz, rchng at 100 MHz, `pcie_0_pipe_clk` at 125 MHz -
and the QMP phy is bound at `1c06000.phy`. So the endpoint is enabled, out of
reset, clocked and powered, on a chip whose Bluetooth half demonstrably works,
and Data Link Layer Link Active never sets.

**Where the kernel's ordering actually goes wrong.** `pci_pwrctrl_create_devices()`
is called from `pci_bus_add_device()` in `drivers/pci/bus.c` - after the bus has
been scanned, therefore after link training. The sequence is necessarily: train
the link with the endpoint unpowered, fail, enumerate nothing, and only then
create the pwrctrl device and power the chip. Nothing re-asserts PERST
afterwards, and PCIe requires PERST# to be held while the endpoint's power comes
up, so the part is left in a state the host cannot talk to. That also explains
why the retrain test failed: the endpoint needs the reset, not the link.

sm8450-hdk does not hit this because its WiFi module's rails are always on.

**The obvious workaround does not work.** Hogging gpio80 high from the tlmm, which
runs far earlier than the controller's 1.3s, was tried: `wlan-enable-gpios` is
optional to pwrseq-qcom-wcn (`devm_gpiod_get_optional`), so Bluetooth kept its own
line and continued to work. gpio80 was high, and the link still never came up.
Reverted rather than left in the tree, because it changed nothing and made the
devicetree describe the hardware less accurately.

Asserting the enable line early is evidently not sufficient on its own - the
chip's external supplies are only voted when the pwrseq powers on, which happens
when Bluetooth probes at around 5.9s, so at 1.3s the part has its enable high and
no rails behind it. Making those rails always-on, or backporting the newer
pwrctrl ordering that defers the host bridge until the endpoint is ready, are the
two remaining approaches. This is a kernel-version limitation and not something
this devicetree can express.

## WiFi: solved

Two changes together, neither sufficient alone.

**Assert the enable line early.** `wlan_en_hog` drives gpio80 high when the tlmm
probes, far ahead of the PCIe controller at ~1.3s. `wlan-enable-gpios` is optional
to `pwrseq-qcom-wcn` (`devm_gpiod_get_optional`), so the pmu node simply stops
claiming it and Bluetooth keeps its own line.

**Hold the rails on.** Hogging alone changed nothing, because the WCN6855's
external supplies are only voted when the pwrseq powers up - which happens when
Bluetooth probes, seconds after PCIe has already given up. The five rails behind
this part (`pm8350_s10`, `pm8350_s11`, `pm8350_s12`, `pm8350c_s1`, `pmr735a_s2`)
are now `regulator-always-on` / `regulator-boot-on`, so the chip has power from
boot.

With both in place the endpoint is enabled, powered and out of reset before the
controller ever looks for it:

```
qcom-pcie 1c00000.pcie: PCIe Gen.2 x1 link up
pci 0000:01:00.0: [17cb:1103] type 00 class 0x028000 PCIe Endpoint
ath11k_pci 0000:01:00.0: wcn6855 hw2.1
ath11k_pci 0000:01:00.0: fw_version 0x11088c35 ... WLAN.HSP.1.1-03125
```

`wlan0` appears, NetworkManager manages it, and scanning returns real networks.

The underlying kernel ordering is still wrong - `pci_pwrctrl_create_devices()`
runs from `pci_bus_add_device()`, after the bus scan and therefore after link
training - and a newer kernel that defers the host bridge until the pwrctrl is
ready would make both of these unnecessary. Until then this is the devicetree
sidestepping the problem by ensuring the endpoint never needs to be powered late.

One loose end: `permaddr` reads `00:03:7f:12:38:b7`, an Atheros default rather
than this device's factory MAC (`4c:e0:db:31:f3:d8`, in
`/persist/qca6490/wlan_mac.bin`). ath11k takes it from board data/OTP, which is
evidently not provisioned for it here. NetworkManager randomises the in-use
address anyway, so this only matters for MAC filtering or DHCP reservations.

## On-screen keyboard: skipped by autostart

stevia was installed (`stevia-0.57.0`, plus `postmarketos-ui-phosh-default-osk`),
`screen-keyboard-enabled` was true for the session, and the binary ran perfectly
when started by hand inside the session. It simply never started on its own.

The reason is one line in `/usr/share/applications/sm.puri.OSK0.desktop`:

```
OnlyShowIn=Phosh;
```

and the session reports `XDG_CURRENT_DESKTOP=GNOME`, because autologin runs
`phosh-session` under `gnome-session`. Autostart therefore skipped the entry
entirely, so tapping a text field produced nothing.

Copied into `/etc/xdg/autostart/` with `OnlyShowIn` (and
`X-GNOME-HiddenUnderSystemd`) removed, from the device package's post-install.
The keyboard now starts with the session and survives a reboot.

## Audio: still blocked on the ADSP handshake

The first command the driver sends the DSP never gets an answer:

```
qcom-apm gprsvc:service:2:1: CMD timeout for [1001021] opcode
```

`0x01001021` is `APM_CMD_GET_SPF_STATE` - the opening handshake with the ADSP's
Signal Processing Framework. Nothing downstream of it can work, which is why
playback returns `-EIO` regardless of routing or topology.

Things tried, none of which changed it:

* **tqftpserv** - was in no runlevel at all (cupid's post-install adds it). Now
  enabled and running.
* **pd-mapper** - built from pmaports and installed, but it exits with
  `no pd maps available`. Enabling EROFS in the kernel finally allowed the
  Android vendor partition to be mounted, and there are **no `.jsn` files
  anywhere on it**, so this device does not use PD maps and pd-mapper is a dead
  end here.
* **DSP firmware** - the `dsp` partition holds the ADSP's audio modules
  (`*_module.so.1`) and fastrpc shells. Extracted and placed at `/vendor/dsp`,
  the Android path, in case the DSP requests them over tqftpserv. No change.

Also confirmed while looking: mainline's audioreach stack has **no TDM support
at all**. `audioreach.c`'s hardware-endpoint switch handles only I2S, CODEC_DMA,
DisplayPort and shared memory; TDM exists solely in the older q6afe/APR stack
that this SoC does not use. So even past the handshake, zeus's four CS35L41 amps
on `TERTIARY_TDM_RX_0` would need TDM endpoint support written in the kernel.

Useful find for later: the vendor partition carries the amps' own DSP firmware -
`BH/BL/TH/TL-cs35l41-dsp1-spk-prot.bin` and `-cali.bin` - which the CS35L41
driver will want for speaker protection once there is a working path to them.

Audio is therefore two problems deep: an ADSP that does not answer, and behind
it a driver stack with no TDM. Neither is a devicetree fix.

### WiFi, properly: retry training with an endpoint reset

The devicetree-only fix turned out to be **racy**, not correct. It worked on one
kernel and failed on the next: enabling EROFS made the kernel slightly larger,
boot timing shifted, and `Phy link never came up` came back with the hog present
and the rails held on exactly as before. A fix that depends on winning a race is
not a fix.

The real problem is that PCIe requires PERST# to be held across the endpoint's
power-on, and `pci_pwrctrl_create_devices()` runs from `pci_bus_add_device()` -
after the bus scan, so after training. If the endpoint comes up even slightly
late, PERST has already been released and no amount of retraining recovers it,
because it is the *endpoint* that needs the reset.

`0004-pcie-qcom-retry-link-training-with-endpoint-reset.patch` makes
`qcom_pcie_start_link()` wait for the link and, if it is down, assert and
deassert PERST before trying again, three times. `qcom_ep_reset_deassert()`
already holds PERST for the 100 ms the spec requires, so a retry only costs that
when the link is genuinely down - a healthy boot pays nothing.

The devicetree changes are kept, because powering the endpoint early is still the
right description of this board and means the retry is rarely needed. Across
reboots the link now comes up on the first attempt at ~0.4-0.55 s, `wlan0`
appears every time, and scanning returns networks.

## Corner touches: a regression of my own making

The bottom-left and bottom-right keys of the on-screen keyboard did not respond.
That was the palm-rejection patch: it also suppressed contacts inside two corner
boxes, converted from stock's `fts,touch-cornerzone-filter-ver`.

When that went in, coordinates were still being decoded in the wrong resolution,
so every touch landed squashed into the top-left and the corner boxes never
triggered - the `rejected id` count stayed at zero and I read that as the patch
being inert. Fixing the super-resolution decode made coordinates correct, and
those boxes then covered real screen: the bottom corners of the keyboard.

The geometric zones are removed. Palm rejection stays, because that is the
firmware classifying the contact rather than a bounding box guessing. Downstream
applies its zone tables through firmware tuning with far more context than a
rectangle, and approximating that here does more harm than good.

## Notch / display cutout

Phosh does support cutouts - `gm_display_panel_get_cutouts` in phosh, an
`xx-cutouts-v1` protocol in phoc, and log strings like *"Notch overlaps left: %d,
right: %d"* and *"No clock placement found to fully avoid notch"*.

The data comes from **gmobile**, keyed on the devicetree `compatible` - here
`xiaomi,zeus` - as a JSON panel description:

```json
{"name":"Xiaomi POCO F1","x-res":1080,"y-res":2246,"border-radius":104,
 "width":68,"height":145,
 "cutouts":[{"name":"notch","path":"M 834,0 c -10.516,0 ..."}]}
```

gmobile 0.7.3 loads these with `g_resources_lookup_data()` - **compiled-in
GResource only**. `/usr/share/gmobile/devices/` exists but is not a search path,
so a file dropped there is ignored; adding zeus means rebuilding gmobile with the
definition included.

`src/gmobile/xiaomi,zeus.json` holds a first cut, but its geometry is an
**estimate**: a 90px-diameter punch-hole centred at (720, 95), derived from the
1440x3200 panel over 70x156mm (20.57 px/mm) and the 12 Pro's roughly 4mm camera
aperture. Android's real value lives in `framework-res.apk`'s
`config_mainBuiltInDisplayCutout`, which is compressed inside the APK and needs
Android resource tooling to extract - `strings` on the partitions does not reach
it.

Shipping a guessed cutout is worse than shipping none: phosh would route the
clock and status icons around the wrong region. So this is prepared but not
built in, pending either the real figure from framework-res or one visual check
against the hardware.

## WiFi instability: what the board data experiments showed

WiFi works from boot and scans, but WMI commands intermittently time out, and in
one session the endpoint dropped off the bus entirely:

```
ath11k_pci 0000:01:00.0: pci device id mismatch: 0xffff 0x1103
pcieport 0000:00:00.0: PCIe Bus Error: severity=Uncorrectable (Non-Fatal)
ath11k_pci 0000:01:00.0: AER: can't recover (no error_detected callback)
```

`0xffff` is config space reading all ones - the device had gone. The root port's
AER fatal counter shows `SDES 1`, Surprise Down: the link vanished rather than
erroring, which is what a chip reset looks like from the host side. ath11k has no
`error_detected` callback, so the PCI core cannot recover it.

The obvious suspect was board data. The device reports **`board_id 0xff`**, and
linux-firmware's `board-2.bin` for WCN6855 hw2.1 is only a symlink to the hw2.0
container, so ath11k falls back to generic calibration - which also explains the
`permaddr` changing between boots.

Two attempts to supply the device's real board data, both **failed and reverted**:

1. **Raw BDF as `board.bin`.** Android keeps 173 of them on the modem partition
   (`/mnt/m/image/bdwlan.e01`..., plus `bdwlan.elf` as the default), each 59932
   bytes. They are ELF-wrapped, so `scripts/`-style extraction pulls the single
   PT_LOAD segment out as a 58180-byte blob. Result:
   `failed to wait board file download request: -110`.
2. **A proper `board-2.bin` container.** Built to ath11k's format - magic
   `QCA-ATH11K-BOARD\0` padded to 4, then nested IEs - keyed to the exact name
   ath11k asks for, `bus=pci,vendor=17cb,device=1103,subsystem-vendor=17cb,
   subsystem-device=0108,qmi-chip-id=18,qmi-board-id=255`. Result, immediately at
   probe: `firmware crashed: MHI_CB_EE_RDDM`.

So the vendor BDF is not interchangeable with the firmware ath11k ships; the
downstream cnss driver and the mainline ath11k firmware expect different board
data. Both changes are reverted and the stock container is back in place.

Current state, measured passively over several minutes: scanning returns six
networks consistently, no firmware crashes, and the endpoint stays on the bus,
with WMI timeouts accumulating slowly in the background.

A note on method: `retrain.py` **sets the Link Control retrain bit**, so polling
with it perturbs the link being measured - a WMI timeout appeared right after one
such poll. It is a one-shot diagnostic, not a monitor.

## Notch: applied without rebuilding gmobile

gmobile loads display-panel definitions with `g_resources_lookup_data()`, so they
have to be compiled into the library and `/usr/share/gmobile/devices/` is not a
search path. Upstream has no entry for zeus, so phosh never learned this panel
has a punch-hole.

Rebuilding gmobile is not necessary. GLib honours **`G_RESOURCE_OVERLAYS`**,
which maps a resource path to a file on disk, and gmobile looks the panel up by
the devicetree compatible - here `xiaomi,zeus` - at a fixed path. Pointing that
one resource at a file is enough:

```
G_RESOURCE_OVERLAYS=/mobi/phosh/gmobile/devices/display-panels/xiaomi,zeus.json=/usr/share/gmobile/devices/display-panels/xiaomi,zeus.json
```

Set from `/usr/local/bin/zeus-phosh-session`, which the autologin session runs
instead of `phosh-session`. The log confirms it takes:

```
Mapped file '/usr/share/gmobile/devices/display-panels/xiaomi,zeus.json' as a resource overlay
phoc-cutouts-overlay-DEBUG: Found panel 'Xiaomi 12 Pro'
phoc-output-DEBUG: Adding cutouts overlay
```

The wrapper also sets `PHOC_DEBUG=cutouts`, which makes phoc draw the cutout
region on screen. That is deliberate for now: the geometry is still an estimate -
a 90px punch-hole centred at (720, 95), derived from 1440px over 70mm and a ~4mm
camera - because Android's real figure sits inside `framework-res.apk` and needs
Android resource tooling to read. Drawing it is the cheapest way to check it
against the actual camera, and the line should come out once the numbers are
confirmed.

Both the JSON and the wrapper ship from the device package, and the post-install
switches greetd's `initial_session` over to the wrapper.

## Stability: let ath11k recover when the firmware stops answering

The WiFi firmware wedges: WMI commands start returning -EAGAIN and never
recover. `ath11k_wmi_cmd_send()` logs the timeout and returns, and nothing above
it reacts, so callers retry for ever. The visible result is a `wlan0` that is up
but cannot scan - and, because the driver's workqueue stays blocked, **a machine
that will not shut down**. Three reboots during this work sat in D state behind a
stuck `kworker/+events` while uptime kept climbing; `sysrq-b` was what actually
got through.

A firmware *crash* is handled - MHI's RDDM path queues `reset_work`. A silent
timeout is not.
`0005-ath11k-reset-the-firmware-when-wmi-stops-answering.patch` counts
consecutive unanswered commands and, after five, asks for the same reset.
`ath11k_core_reset()` already rate limits itself through `fail_cont_count` and
ignores the request before the device is registered, so it cannot spin. The
counter is cleared on any successful command.

This does not stop the firmware wedging - that is the generic board data, which
cannot be fixed from here - but it should turn a wedge from "reboot the phone"
into a few seconds of dropped WiFi.

## CPU policy

conservative governor on all three clusters, with the big ones capped: policy4
(cores 4-6) at 1881600 from 2496000, policy7 (prime) at 1728000 from 2841600.
Both are real entries in the SoC's frequency tables.

`conservative` is a **module** in this kernel and does not appear in
`scaling_available_governors` until loaded - writing the name before that fails
silently, which is worth knowing before concluding the governor is unsupported.
`/etc/local.d/zeus-cpufreq.start` loads it and applies everything;
`/etc/udev/rules.d/50-cpufreq.rules` re-runs it when a CPU appears, so the policy
survives hotplug rather than only boot.

## Camera: not portable to this device

Not a porting job. The CAMSS driver supports msm8916, msm8953, msm8996, sc7280,
sc8280xp, sdm660, sdm845 and sm8250 - **no sm8450** - and `sm8450.dtsi` contains
no camss node at all. There is nothing to enable: this SoC's camera subsystem has
no mainline driver, so supporting it means writing a new CAMSS variant and its
devicetree, which is upstream-scale work rather than configuration.

## Audio: tqftpserv ordering ruled out

`tqftpserv` was in no runlevel at all and is now enabled at boot, starting before
the ADSP comes up at ~6.6s. `APM_CMD_GET_SPF_STATE` still times out at ~12s, so
the ADSP not being able to fetch files was not the cause either. That theory
joins pd-mapper and the DSP firmware placement in the ruled-out list.

## Why SPF never started: we were deaf to the answer

It was not the ADSP. Tracing every packet across the GPR link showed the ADSP
answering all along - 155 packets each way - and the reply to the SPF query
arriving **4ms** after the request:

```
10.513  GPRTRACE tx  src_port=0x1 dst_port=0x1 opcode=0x1001021   (GET_SPF_STATE)
10.517  GPRTRACE rx  src_port=0x1 dst_port=0x1 opcode=0x2001007   (the response)
15.586  qcom-apm: CMD timeout for [1001021] opcode
```

The right opcode, to the right port, five seconds before the timeout was
reported. The packet was being thrown away:

```c
static int apr_device_probe(struct device *dev)
{
	ret = adrv->probe(adev);
	if (!ret)
		adev->svc.callback = adrv->gpr_callback;   /* too late */
	return ret;
}
```

The callback is installed **after** the driver's probe returns, and
`q6apm_probe()` sends `GET_SPF_STATE` from inside probe.
`gpr_do_rx_callback()` finds the service, sees `svc->callback` is NULL and
returns without a word - the silent drop is why nothing in the log ever pointed
at it. The caller then waited out its full five seconds for a reply that had
already arrived.

That also explains why polling did not help: every retry happens inside the same
probe, so every response is dropped. Any driver that sends a command from probe
and waits for the answer hits this; q6apm is simply the one that does.

`0008-apr-install-the-gpr-callback-before-probing.patch` installs the callback
first and clears it if probe fails. Nothing can be delivered before the device
exists, so this is safe.

Result: `CMD timeout` went from 6 per boot to **0**, and `speaker-test` now
reaches "Front Left" where it used to fail instantly.

Playback still ends in -EIO, with no kernel error at all now. That is a routing
problem rather than a DSP one, and the known gap is still the topology: the HDK
file this device borrows has no TDM backend, so nothing in it can reach zeus's
four CS35L41 amps. But the DSP itself is finally talking.

## Audio plays: the card needed a UCM profile

With the GPR callback fix the DSP handshake succeeds, but playback still ended in
-EIO and the sound server showed a **Dummy Output**. Both had the same cause: no
ALSA use case manager profile matched this card.

alsa-lib looks for `conf.d/<card driver>/<card name>.conf`, which for this device
is `sm8450/Xiaomi-12.conf`, and nothing shipped one. Without it the codec routing
is never set up - the DSP writes into a path that goes nowhere, the ring never
drains, and the stream xruns into -EIO - and the sound server, unable to
configure the card, falls back to a null sink.

The profile is modelled on Qualcomm's own SM8550-HDK: same ADSP architecture,
same wcd938x codec and lpass macros. Its WSA speaker sections are dropped, since
zeus drives four CS35L41 amps over tertiary TDM, a path the borrowed HDK topology
does not describe.

Two things worth remembering about testing it. `alsaucm` is stateless between
invocations, so the verb has to be set in the same command as the device -
`alsaucm -c hw:0 set _verb HiFi set _enadev Headphones`, not two calls, or the
device lookup fails with ENOENT and looks like a missing control. And the card
resolves as `hw:0` rather than by name: `alsaucm -c Xiaomi12` fails to import
while `-c hw:0` works.

With the verb and device set, speaker-test completes a full cycle:

```
 0 - Front Left
 1 - Front Right
Time per period = 5.020212
```

and after a reboot the sound server exposes a real sink instead of the null one:

```
alsa_output.platform-sound.HiFi__Headphones__sink  s16le 2ch 48000Hz
```

This is the wcd938x headphone path. The speakers still need a zeus topology with
a TDM backend.

## Where audio actually stands

The software path works end to end. With the UCM verb and device set, the PCM
runs and keeps running:

```
state: RUNNING   delay: 48000   avail: 0
```

Data is being accepted by the DSP continuously, the sound server exposes a real
sink, and speaker-test completes. There is still no audible sound, and the reason
is not software: this route ends at the wcd938x headphone outputs, HPHL/HPHR, and
this phone has no headphone jack. The audio is being played correctly into pins
that go nowhere.

The speakers are four CS35L41 amps on **tertiary** TDM, and reaching them needs
more than a devicetree change:

* audioreach has no TDM support at all - `audioreach.c` handles I2S, CODEC_DMA,
  DisplayPort and shared memory, and there is no TDM module id anywhere in the
  qdsp6 directory. TDM exists only in the older q6afe/APR stack this SoC does not
  use.
* I2S is a real alternative, since the pins are muxed as `mi2s2` and
  `q6apm-lpass-dais` does register MI2S ports with `q6i2s_ops`. But the LPAIF
  interface index comes from the topology - `intf_cfg->cfg.intf_idx =
  module->hw_interface_idx`, read from AR_TKN_U32_MODULE_HW_IF_IDX - and the
  borrowed HDK topology only describes **primary** MI2S (`device16.i2s_rx1`).

So the missing piece is a topology carrying a tertiary MI2S or TDM backend. It
cannot be produced by editing the devicetree, and cloning the primary MI2S
backend inside the binary means re-implementing a good part of the ALSA topology
format - snd_soc_tplg_dapm_widget structures and their private vendor arrays -
with a real risk of producing something the ADSP rejects. A malformed board file
already crashed this chip once, with MHI_CB_EE_RDDM at probe.

That is the honest boundary: everything up to the hardware endpoint works, and
the endpoint the topology can reach is not connected to a speaker on this device.
