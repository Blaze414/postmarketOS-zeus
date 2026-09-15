#!/usr/bin/env python3
"""Attribute a hashed ADSP message to a source file.

Descriptors are laid down per source file, in declaration order, so a hashed
message's file can be named by the nearest descriptors on either side that
still carry a real format string - those strings start with their own file
name.

    qsrfile.py <adsp.mbn> ssid:line:hash [...]
"""
import struct
import sys


def segments(data):
    e_phoff, = struct.unpack_from("<I", data, 0x1C)
    e_ps, e_pn = struct.unpack_from("<HH", data, 0x2A)
    segs = []
    for i in range(e_pn):
        o = e_phoff + i * e_ps
        va, = struct.unpack_from("<I", data, o + 0x08)
        off, = struct.unpack_from("<I", data, o + 0x04)
        fs, = struct.unpack_from("<I", data, o + 0x10)
        if fs:
            segs.append((va, off, fs))
    return segs


def make_v2o(segs):
    def v2o(v):
        for va, off, sz in segs:
            if va <= v < va + sz:
                return off + (v - va)
        return None
    return v2o


def cstr(data, v2o, v, limit=200):
    o = v2o(v)
    if o is None:
        return None
    e = data.find(b"\0", o, o + limit)
    if e < 0:
        return None
    b = data[o:e]
    if len(b) < 10 or not all(32 <= c < 127 for c in b):
        return None
    return b.decode()


def main():
    data = open(sys.argv[1], "rb").read()
    segs = segments(data)
    v2o = make_v2o(segs)

    def o2v(off):
        for va, foff, size in segs:
            if foff <= off < foff + size:
                return va + (off - foff)
        return None

    for spec in sys.argv[2:]:
        ssid, line, want = spec.split(":")
        ssid, line, want = int(ssid), int(line), int(want, 16)
        key = struct.pack("<I", (ssid << 16) | line)

        hit = None
        start = 0
        while hit is None:
            i = data.find(key, start)
            if i < 0:
                break
            start = i + 4
            if i % 4:
                continue
            h, = struct.unpack_from("<I", data, i + 8)
            if h == want:
                hit = i

        if hit is None:
            print(f"{want:08x} line {line}: descriptor not found")
            continue

        def scan(step):
            for n in range(1, 4000):
                off = hit + n * step * 12
                if off < 0 or off + 12 > len(data):
                    return None
                w0, _, ptr = struct.unpack_from("<III", data, off)
                if (w0 >> 16) != ssid:
                    continue
                s = cstr(data, v2o, ptr)
                if s:
                    return (w0 & 0xFFFF, s.split(":")[0])
            return None

        before, after = scan(-1), scan(1)
        print(f"{want:08x} line {line:5d} @0x{o2v(hit):08x}")
        print(f"    before: {before}")
        print(f"    after : {after}")


if __name__ == "__main__":
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    main()
