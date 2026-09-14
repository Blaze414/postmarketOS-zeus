#!/usr/bin/env python3
"""Turn the stock ACDB speaker graph dump into firmware blobs the kernel sends
to the APM verbatim (patch 0013):

  apm-graph-56.bin      APM_CMD_GRAPH_OPEN payload: stock device subgraph
  apm-graph-56-cal.bin  APM_CMD_SET_CFG payload: stock calibration for it

Ids are renamed onto the zeus topology's graph 56 so the kernel's own
prepare/start/close (which address the topology's SG and modules) still hit
them. Connections to modules outside this subgraph are dropped, and the stream
is connected into the head of the stock chain the way stock does it.

    python3 scripts/acdb/mkgraph.py stock-dump/audio/spk-graph.txt out/
"""
import re, struct, sys

SG = {0xb0000002: 0x400a}                 # stock device SG -> topology SG
CONT = {0xe0000002: 0x400a}               # stock container -> topology container
MOD = {0x4007: 0x60a0,                    # DATA_LOGGING -> device56.logger1
       0x4911: 0x60a1,                    # MFC          -> device56.mfc1
       0x4881: 0x60a2}                    # TDM_SINK     -> device56.codec_dma_rx1
# ponytail: only MultiMedia1 (its logger) feeds the stock chain; other FEs need their own conn
STREAM_TAIL, CHAIN_HEAD, CHAIN_HEAD_PORT = 0x6006, 0x4012, 4
APM = 1


def section(txt, name):
    body = re.split(r"\n  " + re.escape(name) + r" rc=\S+[^\n]*:\n", txt)[1]
    body = re.split(r"\n  \S", body)[0]
    return [int(w, 16) for w in re.findall(r"\b[0-9a-f]{8}\b", body)]


def params(ws):
    """Split an APM param stream into (iid, pid, payload words)."""
    i = 0
    while i + 4 <= len(ws):
        iid, pid, size, _ = ws[i:i + 4]
        n = (size + 7) // 8 * 8 // 4
        yield iid, pid, size, ws[i + 4:i + 4 + n]
        i += 4 + n


def pack(iid, pid, size, pl):
    """param_size is the real payload size; the payload is padded to 8 bytes."""
    pl = pl[:(size + 3) // 4]
    return [iid, pid, size, 0] + pl + [0] * ((-len(pl)) % 2)


def device_sg(ws):
    out = []
    for iid, pid, size, pl in params(ws):
        if pid == 0x08001001 and pl[1] not in SG:
            break                           # second SG (stream) starts here
        out.append((iid, pid, size, list(pl)))
    return out


def rename(w):
    return MOD.get(w, SG.get(w, CONT.get(w, w)))


def graph_open(ws):
    sg = device_sg(ws)
    local = set()
    for _, pid, _, pl in sg:
        if pid == 0x08001002:               # MODULE_LIST: 1, sg, cont, n, (mid, iid)*
            local |= set(pl[5:5 + 2 * pl[3]:2])
    blob = []
    for iid, pid, size, pl in sg:
        if pid == 0x08001004:               # MODULE_CONN: n, (src, oport, dst, iport)*
            conns = [pl[1 + 4 * k:5 + 4 * k] for k in range(pl[0])]
            conns = [c for c in conns if c[0] in local and c[2] in local]
            conns.append([STREAM_TAIL, 1, CHAIN_HEAD, CHAIN_HEAD_PORT])
            pl = [len(conns)] + sum(conns, [])
            size = len(pl) * 4
        # ids never collide with module/param ids (0x07.../0x08...), so rename every word
        blob += pack(iid, pid, size, [rename(w) for w in pl])
    return blob


def cal(txt):
    blob = []
    head = txt.split("cal(nonpersist, no ckv)")[1].split("connections rc=")[0]
    for m in re.finditer(r"cal iid=(\w+) pid=(\w+) size=(\d+):\n((?:\s+[0-9a-f ]+\n)*)", head):
        iid, pid, size = int(m[1], 16), int(m[2], 16), int(m[3])
        if iid not in MOD and iid not in (0x4012, 0x418e, 0x40e1):
            continue                        # stream SG modules: not ours
        pl = [int(w, 16) for w in m[4].split()]
        blob += pack(rename(iid), pid, size, pl)
    return blob


def le(ws):
    return b"".join(struct.pack("<I", w) for w in ws)


if __name__ == "__main__":
    txt = open(sys.argv[1]).read()
    g, c = graph_open(section(txt, "subgraph data")), cal(txt)
    assert g[:2] == [APM, 0x08001001] and g[5] == 0x400a, "unexpected SG layout"
    assert all(w not in (0xb0000002, 0xe0000002, 0x4007, 0x4881, 0x4911) for w in g), "id left unmapped"
    open(sys.argv[2] + "/apm-graph-56.bin", "wb").write(le(g))
    open(sys.argv[2] + "/apm-graph-56-cal.bin", "wb").write(le(c))
    assert len(g) % 2 == 0 and len(c) % 2 == 0
    for iid, pid, size, pl in params(g):
        print(f"open {iid:x} {pid:08x} {size:#x} " + " ".join(f"{w:x}" for w in pl))
    print(f"cal {len(c) * 4} bytes")
