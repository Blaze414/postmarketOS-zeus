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

## Milestone 1: built, and it works

The shim is `src/kernel/audio_pkt.c` plus patch 0016 (kernel r55, `#56`), and
the DT node is `service@3` under `gpr` in the zeus dts. `/dev/aud_pasthru_adsp`
appears, the router registers it (`Adding APR/GPR dev: gprsvc:service:2:3`),
and GSL numbers its own ports through `gpr_alloc_port_id()` exactly as planned.

`scripts/gsl/gprprobe.c` does the round trip with no GSL involved - one
APM_CMD_GET_SPF_STATE out, the reply back on the port userspace picked:

```
tx 24 bytes: 00001860 00000302 00002003 00000001 5a5a0001 01001021
rx 28 bytes: 00001c60 00000203 00000001 00002003 5a5a0001 02001007 00000001
opcode 02001007 dest_port 00002003 token 5a5a0001
OK: SPF state = 1
```

Worth noting on its own: q6apm's *own* copy of this handshake times out at
every boot (`qcom-apm gprsvc:service:2:1: CMD timeout for [1001021] opcode`,
~5s in), while the same command from userspace is answered immediately. The
DSP is not slow to answer; something about how the in-kernel client waits is.
That is a loose thread, not yet pulled.

`scripts/gsl/gslprobe.c` then brings up GSL itself against the stock ACDB.
GSL initialises, registers its ports, sends, and is answered - the whole
transport works under the real client. It gets exactly as far as shared
memory and stops:

```
[AOSH ar_shmem_alloc:144] vaddr(0x0xffffa6d98000)
[gpr_dl_lx gpr_dl_lx_send:454] Sending buffer of size 44 to driver
[gpr_dl_lx receiver_thread_loop:257] recieved buffer 2060 b00203 1 2002 size 32
[gsl gsl_shmem_handle_rsp:279] Received unexpected rsp opcode 2001005, expected 2001001
[gsl allocate_page:749] failed to map page with spf error 5
[gsl gsl_do_load_bootup_dyn_modules:323] failed to register dynamic modules 5
[gsl gsl_init:1104] dynamic module load failed 5
```

APM_CMD_SHARED_MEM_MAP_REGIONS is refused (the DSP answers
GPR_BASIC_RSP_RESULT 0x2001005 instead of 0x2001001) because the page handed
to it is an ordinary malloc'd one - `ar_osal_shmem_virtual.c`, chosen
deliberately, since the control path was the question. The DSP cannot reach
that memory.

So milestone 1 is answered in full: **the transport is not the problem, and
mainline needs no more than this shim to carry it.** What blocks the actual
experiment is what the scoping said it would be, now confirmed rather than
predicted: shared memory.

## What milestone 2 has to do

GSL needs pages the ADSP can map. The mainline pieces already exist:

- `q6apmdai` in the devicetree carries `iommus = <&apps_smmu 0x1801 0x0>`,
  the ADSP's stream id - it is the device q6apm-dai already allocates
  playback buffers against.
- dma-heap gives userspace an allocator with a dma-buf fd.
- `ar_osal_shmem_db.c` in graphservices is *already* the dma-heap backend -
  it wants `linux/msm_audio.h` only for the ioctl that asks the kernel to map
  a buffer into the DSP's context.

So the shape is: give `audio_pkt` an ioctl that hands back memory the DSP can
reach, and point `ar_osal_shmem` at it instead of at msm_audio.

## Milestone 2: done, and GSL opens the speaker graph

Simpler than importing a dma-buf: the kernel allocates. `AUDIO_PKT_IOCTL_ALLOC`
plus `mmap()` give userspace a `dma_alloc_coherent()` buffer taken against a
new `memory` child of the GPR service node with
`iommus = <&apps_smmu 0x1801 0x0>` - the ADSP's stream id. It lands in the
same IOMMU group as `q6apmdai`:

```
# ls /sys/kernel/iommu_groups/19/devices/
30000000.remoteproc:glink-edge:gpr:service@1:dais
30000000.remoteproc:glink-edge:gpr:service@3:memory
```

and the address returned is the dma address with the stream id in the top
bits, composed exactly as q6apm-dai composes `prtd->phys`. The child needs a
driver bound to it only so the bus runs `of_dma_configure()`; hence the
trivial platform driver beside the main one.

`scripts/gsl/ar_osal_shmem_audio_pkt.c` is ar_osal_shmem over that ioctl.
Because the real address is known in userspace, buffers are reported in
address mode (`AR_SHMEM_BUFFER_ADDRESS`, `AR_SHMEM_PHYSICAL_MEMORY`) and GSL
leaves `client_data` clear - the Android stack's trick of having the kernel
substitute a physical address on the way past is not needed.

One local edit to graphservices was needed (`scripts/gsl/patch-gs.py`):
`gsl_init` treats a failed dynamic AMDB module load as fatal, and the DSP
cannot load those modules here. They are aptX, LC3 and an Elliptic ultrasound
module, whose `.so` files the DSP fetches from the Android vendor partition
over rfsa - which pmOS has no counterpart to. None is on the path to the
speakers.

With that:

```
gsl_init: 0 (OK)
```

### The experiment, at last

Opening the stock speaker graph by its key vector
(`a1000000=a1000003 a2000000=a2000001`, doc 11):

| command | opcode | spf_status |
|---|---|---|
| `gsl_open` | 0x1001000 GRAPH_OPEN | **0** |
| | 0x1001006 SET_CFG | **0** |
| `GSL_CMD_PREPARE` | 0x1001001 GRAPH_PREPARE | **0** |
| `GSL_CMD_START` | 0x1001002 GRAPH_START | **1** |

The DSP **accepts** the stock speaker graph - open, configure and prepare all
succeed, where the in-kernel path could not get a TDM sink configured at all.
GRAPH_START is then refused with a bare AR_EFAILED and no detail.

So the premise holds further than milestone 1 could show, and the remaining
failure is a new one, not the old `media_format_set:0` wall.

## Chasing GRAPH_START

### The DSP's log does not say

Captured the ADSP's F3/QShrink stream across a start (`scripts/diag`). SSID
8500 messages around the failure are all hashed:

```
hash=70cae291 line=46   args=['0x1001000', '0xe000']     # GRAPH_OPEN received
hash=9d598de9 line=2931 args=['0x4007', '0x8001026']     # PARAM_ID_MODULE_ENABLE
hash=64d6db7b line=365  args=['0x10016000', '0x4015', '0x1']
hash=fb2c882e line=367  args=['0x10016000', '0x2e', '0x0']
```

The only QShrink database on the phone is the modem's, and none of these
hashes are in it. `scripts/diag/qsrfind.py` locates a hash's 12-byte log
descriptor `{ssid<<16|line, ss_mask, hash}` in `adsp.mbn` and prints its
neighbours, in the hope that a nearby call site in the same source file kept
a real format pointer. For this region none did - the whole block is hashed.
Resolving these would mean tracing the code that references each descriptor,
which is where doc 11's disassembly work ended up too.

### Differential testing says plenty

Far more informative, and much cheaper: **run the same probe against a graph
that has nothing to do with the speakers.** The headphone playback graph
(`a1000000=a1000003 a2000000=a2000002`) behaves *identically* - open,
configure and prepare succeed, start fails with the same bare error.

So GRAPH_START is not the DSP refusing the speaker path. Something about
this environment stops **every** graph from starting, and doc 11's picture -
that the TDM endpoint is uniquely unreachable - does not carry over here.

Two candidates ruled out along the way:

- **The data path.** Adding `GSL_CMD_CONFIGURE_WRITE_PARAMS` before prepare
  succeeds, so the shared-memory write endpoint provisions correctly. The
  buffers from milestone 2 work for data, not just for control.
- **Coexistence.** Running `aplay` at the same time makes GSL's GRAPH_OPEN
  fail instead - the DSP does enforce exclusivity, which incidentally
  confirms that a successful open really does claim the path.

### Where it stands: nothing has powered the audio core

In the Android stack the client asks the DSP's proxy resource manager for
hardware resources before starting a graph -
`gsl_request_hw_rsc_config()` / `gsl_request_hw_rsc_custom_config()` in
`gsl/hw_rsc_api/gsl_hw_rsc_intf.h`. Nothing inside GSL calls these; they are
the client's job. Under mainline, q6prm does the equivalent when ASoC brings
a path up. A graph opened straight from userspace goes through neither, so
the LPASS core is never voted on - and a hardware endpoint cannot start with
its core unpowered. That fits the symptom exactly: every graph opens and
prepares, every graph fails to start.

`gslprobe` now issues that vote (PARAM_ID_RSC_HW_CORE / HW_CORE_ID_LPASS to
PRM_MODULE_INSTANCE_ID). The DSP **receives** it - the diag log shows
`hash=24cce70d line=54 args=['0x100100f']`, which is PRM_CMD_REQUEST_HW_RSC -
but never answers, and the request times out (AR_ETIMEOUT). The payload shape
is inferred from `hw_core_api.h` and is the most likely thing to be wrong.

That turned out not to be it. The LPASS core is **already voted on** - the
codec macros hold it, and have since boot:

```
# grep LPASS_HW /sys/kernel/debug/clk/clk_summary
 LPASS_HW_DCODEC   4  4  ...  Y  3220000.codec  dcodec
 LPASS_HW_MACRO    4  4  ...  Y  3220000.codec  macro
```

So the core being unpowered cannot be the reason, and there was no need to
have the kernel hold the vote. (GSL's own request still times out - the DSP
receives PRM_CMD_REQUEST_HW_RSC and does not answer - so the payload shape
guessed from `hw_core_api.h` is wrong, but it no longer matters here.)

## What GRAPH_START is not

Each of these was tested on the device and eliminated:

| Suspect | Test | Result |
|---|---|---|
| Speaker/TDM specific | headphone graph `a2000000=a2000002` | fails identically |
| Any hardware endpoint | `a1000000=a1000013`, stream only, no device | fails identically |
| Any stream | `a2000000=a2000001`, device only, no stream | fails identically |
| LPASS core unpowered | `clk_summary` | already voted, count 4 |
| Data path not provisioned | `GSL_CMD_CONFIGURE_WRITE_PARAMS` | succeeds |
| Broken AMDB state after the failed module load | `GSL_SKIP_DYN_MODULES=1`, leaving AMDB untouched | fails identically |
| Stream media format never set | `PARAM_ID_MEDIA_FORMAT` to the endpoint tagged `c0000001` (WR_SHMEM_EP, miid 0x458e) before prepare | accepted, still fails |
| Another client holding the path | with `aplay` running, GRAPH_OPEN fails instead | not the case when idle |

So: GRAPH_OPEN, SET_CFG, media format, write-params and GRAPH_PREPARE are all
accepted for every graph tried, and GRAPH_START is refused for every graph
tried, with a bare AR_EFAILED and nothing in the DSP log that resolves.

Worth keeping in view: the kernel's own graphs *do* start on this DSP right
now - headphone playback through ALSA works. So the DSP is not refusing
GRAPH_START as such. It is refusing these graphs, or refusing this client.

### Tag map, as a by-product

`scripts/acdb/acdbtag.c` gives the module tags per graph, which is how the
media-format endpoint was found:

```
a1000000=a1000013                  c0000001: 07001000/458e   WR_SHMEM_EP
a1000000=a1000003 a2000000=a2000001 c0000004: 0700100e/4881  TDM_SINK
                                    c0000040: 07001098/40e1  MUX_DEMUX
a1000000=a1000003 a2000000=a2000002 c0000004: 07001023/43b2  CODEC_DMA_SINK
```

Note that the speaker and headphone graphs carry no WR_SHMEM_EP tag: stream
`a1000003` puts it elsewhere, so a real playback client would have to find it
by module id rather than by tag.

## The side-by-side capture: GRAPH_START was never the failure

Patch 0017 adds optional GPR packet tracing to the router
(`/sys/module/apr/parameters/gpr_trace`). Every client - q6apm, q6prm and
userspace through audio_pkt - goes through `pkt_router_send_svc_pkt()` and
`gpr_do_rx_callback()`, so one tap sees them all.

The two GRAPH_START packets are **structurally identical**:

```
kernel  tx  00004060 00000302 00000001 00000001 00000000 01001002 00000000 00000000
            00000000 00000018 00000001 08001005 00000008 00000000 00000001 00004001
        rx  ... 02001005 01001002 00000000        <- status 0
GSL     tx  00004060 00000302 00002010 00000001 00013000 01001002 00000000 00000000
            00000000 00000018 00000001 08001005 00000008 00000000 00000001 b00000d6
        rx  ... 02001005 01001002 00000001        <- status 1
```

Same size, same domains, same destination, same `apm_cmd_header_t`
(payload_size 0x18), same parameter (APM instance 1,
APM_PARAM_ID_SUB_GRAPH_LIST 0x08001005, size 8), same count. The only field
that differs is the subgraph id being started. So the command is well formed
and the client is not the problem.

**And GRAPH_START is not the first failure.** Scrolling back in the same
capture:

```
GSL  tx  ... 01001006 ffdf8800 00000001 / b0d6b8c8 000002b8   <- SET_CFG, 696 bytes OOB
     rx  ... 02001005 01001006 00000003                       <- status 3, AR_EUNSUPPORTED
```

Every one of the kernel's SET_CFGs returns 0. GSL's 696-byte configuration
SET_CFG is **rejected as unsupported**, immediately after GRAPH_OPEN - and
GSL does not treat that as fatal, so it was invisible from the API. The later
GRAPH_START failure is a consequence of a graph whose modules were never
configured, not a cause.

696 bytes is exactly the size of this graph's non-persistent calibration
(`acdbq` reports `cal(nonpersist, no ckv) rc=0 size=696`) - 25 parameters
across module instances 0x458e-0x4598.

### Correction: AMDB is not eliminated

The earlier elimination table says AMDB was ruled out because
`GSL_SKIP_DYN_MODULES=1` changed nothing. That test only shows the *attempt*
to register modules does not matter. It does not show the modules are
present - they are absent either way, since the DSP fetches their .so files
over rfsa, which does not exist here. If one of the module instances in that
calibration blob belongs to a module that was never loaded, SPF would answer
exactly as observed.

That is the leading hypothesis now, and unlike the previous ones it predicts
something checkable: identify which of the 25 parameters SPF refused.

## Leads left

- **Find the refused parameter.** SPF returns EUNSUPPORTED for the whole
  SET_CFG if any one parameter is unsupported, but it writes a per-parameter
  `error_code` back into the out-of-band payload - which lives in memory this
  port allocates, so it can be read back. Splitting the blob and sending one
  parameter at a time would do as well. Either names the module.
- **Then check that module against AMDB.** If it is one of the dynamically
  loaded ones, the fix is to serve those .so files to the DSP (an rfsa
  equivalent) or to drop the parameters belonging to them.
- **ACDB version skew.** The calibration key-vector tables fail to parse
  (error 17, "CKV key table and value table offsets"), and no persistent
  calibration is found for subgraphs b0000002/b0000006. If this graphservices
  checkout misreads parts of a vendor database written for an older ACDB, the
  subgraph blobs sent at GRAPH_OPEN could be subtly wrong in a way the DSP
  only acts on at start. Only one ACDB file is loaded here; Android loads
  several.
- **Resolving the DSP's own messages** would end the guessing, but needs the
  ADSP QShrink database, which is not on the phone - or tracing the code that
  references each log descriptor, as in doc 11.
