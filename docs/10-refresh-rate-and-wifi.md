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
