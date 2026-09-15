# Porting Android's AudioReach userspace (GSL/AGM) to postmarketOS

Scoping spike for the one remaining route to internal speakers. Doc 11 ends with
the finding that mainline's in-kernel q6apm never gets the DSP to propagate a
media format to a **TDM** hardware-endpoint sink, while Android drives that exact
firmware fine from userspace (GSL/AGM + ACDB). This is the scope of running that
userspace on pmOS instead.

Not started as an implementation - this records what the spike proved.

## The transport contract is trivial

`gpr/datalinks/gpr_lx/src/gpr_lx.c` in audioreach-graphservices is the whole
Linux transport. It opens a character device and does raw GPR packets:

```
#define GPR_DL_LX_ADSP_DRV "/dev/aud_pasthru_adsp"
...
dl_lx_port->drv_fd = open(drv_name, O_RDWR);
receive_size = read(dl_lx_port->drv_fd, buf, GPR_DL_LX_BUF_SIZE);
status      = write(dl_lx_port->drv_fd, buf, size);
poll(pfd, NUM_FDS, -1);
```

So the kernel side is a char device `/dev/aud_pasthru_adsp` supporting
open/read/write/poll of raw GPR packets. Nothing more.

## Mainline already has the plumbing for it

`include/linux/soc/qcom/apr.h` exposes exactly what such a shim needs:

```
gpr_port_t *gpr_alloc_port(gpr_device_t *gdev, struct device *dev,
                           gpr_port_cb cb, void *priv);
int gpr_send_port_pkt(gpr_port_t *port, struct gpr_pkt *pkt);
```

- **TX**: `pkt_router_send_svc_pkt()` does **not** rewrite the header - it
  `rpmsg_trysend()`s the packet verbatim. Userspace packets reach the DSP as-is.
- **RX**: `gpr_do_rx_callback()` routes by `hdr->dest_port` via
  `idr_find(&gpr->svcs_idr, ...)`, delivering to that port's callback.

One wrinkle: GSL picks its own `src_port` numbering, and the DSP echoes it back
as `dest_port`. `gpr_alloc_port()` only allocates *cyclic dynamic* ids, so the
shim must either (a) gain a small helper to register a port at a **specific** id,
or (b) rewrite `src_port` outbound and reverse-map it inbound. (a) is closer to
how Android's `audio_pkt` works.

Estimate: ~200-300 lines of kernel driver plus a few lines in `apr.c`.

## GSL builds on musl/aarch64 essentially as-is

Built in the pmbootstrap Alpine aarch64 chroot (`gcc`, musl), per-file:

| component | compiled |
|---|---|
| GSL core (`gsl/src/*.c`) | **18/18** |
| GPR core + `gpr_lx` datalink | **3/3** |
| ACDB (`acdb/src/*.c`) | 11/12 |
| ar_osal Linux (`ar_osal/src/linux`) | 10/11 |

Everything needed was `-D__unused=` (a bionic-ism), `-D_GNU_SOURCE` (for
`pthread_setname_np`, which musl has) and the right include set - 47 header
dirs, notably `gpr/core/inc/ar_utils/generic` (not the hexagon/audioss variants)
and the nested `spf/api/*` dirs. Reproduce with `scripts/gsl/build-probe.sh`.

Android-only pieces, all optional in `configure.ac`:

- `ar_osal_log.c` needs `log/log.h` (cutils) - configure has `--with-syslog`.
- `ar_osal_signal2.c` uses `ALOGE` - unused; `ar_osal_signal.c` is the one built.
- `ar_osal_shmem_phy.c` needs `linux/msm_audio.h` - see below, the real work.

## What is actually hard: shared memory

The control path above is cheap. Playing audio needs buffers the ADSP can read,
which on Android is ION/dma-buf via `msm_audio_ion`, mapped into the ADSP's
SMMU. `ar_osal_shmem_*` is the OSAL seam for it, and the mainline equivalent
(dma-heap + the audio SMMU context q6apm-dai already uses) has to be written.
That, not the build, is the engineering.

## Suggested order

1. **Control path only.** `audio_pkt` shim + GSL built above; have GSL open the
   stock speaker graph from the ACDB. If the TDM sink then accepts a media
   format where mainline's q6apm cannot, the whole premise is validated - and
   that is the single most informative experiment available.
2. **Data path.** dma-heap shmem OSAL + kernel mapping into the ADSP SMMU.
3. **Coexistence + integration.** Decide who owns the DSP (in-kernel q6apm for
   headphones/USB vs GSL for speakers - graph handles are independent, but this
   needs care), then bridge to ALSA/PulseAudio (AGM's tinyalsa plugins or a
   dedicated sink).

Step 1 is bounded and answers the question. Steps 2-3 are the multi-week part.
