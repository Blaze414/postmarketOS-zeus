#!/usr/bin/env python3
"""Minimal A/B OTA payload.bin extractor (full OTAs only), no dependencies.
usage: payload.py <zip> <outdir> [partition ...]   (no partitions = list)"""
import bz2, lzma, struct, sys, zipfile, os, hashlib
import compression.zstd as zstd


def varint(b, i):
    v = s = 0
    while True:
        c = b[i]; i += 1; v |= (c & 0x7f) << s; s += 7
        if c < 0x80:
            return v, i


def fields(b):
    i, out = 0, []
    while i < len(b):
        k, i = varint(b, i); f, t = k >> 3, k & 7
        if t == 0:
            v, i = varint(b, i)
        elif t == 2:
            n, i = varint(b, i); v = b[i:i + n]; i += n
        elif t == 5:
            v = b[i:i + 4]; i += 4
        elif t == 1:
            v = b[i:i + 8]; i += 8
        else:
            raise ValueError(t)
        out.append((f, v))
    return out


z = zipfile.ZipFile(sys.argv[1])
info = z.getinfo("payload.bin")
fh = open(sys.argv[1], "rb")
fh.seek(info.header_offset)
h = fh.read(30)
base = info.header_offset + 30 + struct.unpack_from("<H", h, 26)[0] + struct.unpack_from("<H", h, 28)[0]
assert info.compress_type == 0
fh.seek(base)
magic, ver, msize = struct.unpack(">4sQQ", fh.read(20))
assert magic == b"CrAU" and ver == 2
sigsize = struct.unpack(">I", fh.read(4))[0]
manifest = fields(fh.read(msize))
data0 = base + 24 + msize + sigsize
bs = next((v for f, v in manifest if f == 3), 4096)
parts = {}
for f, v in manifest:
    if f == 13:
        pf = fields(v)
        name = next(x for k, x in pf if k == 1).decode()
        parts[name] = [fields(x) for k, x in pf if k == 8]
if len(sys.argv) < 4:
    for n, ops in parts.items():
        print(n, len(ops))
    sys.exit()
for name in sys.argv[3:]:
    out = open(os.path.join(sys.argv[2], name + ".img"), "wb")
    for op in parts[name]:
        d = dict((k, v) for k, v in op if k not in (6,))
        t, off, ln = d.get(1, 0), d.get(2, 0), d.get(3, 0)
        ext = [dict(fields(x)) for k, x in op if k == 6]
        fh.seek(data0 + off)
        raw = fh.read(ln)
        if t == 0:
            blob = raw
        elif t == 1:
            blob = bz2.decompress(raw)
        elif t == 8:
            blob = lzma.decompress(raw)
        elif t == 14:
            blob = zstd.decompress(raw)
        elif t in (6, 7):
            blob = None
        else:
            raise ValueError(f"op type {t}")
        pos = 0
        for e in ext:
            s, nb = e.get(1, 0), e.get(2, 0)
            out.seek(s * bs)
            if blob is None:
                out.write(b"\0" * nb * bs)
            else:
                out.write(blob[pos:pos + nb * bs]); pos += nb * bs
    out.truncate()
    print(name, out.tell())
