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
