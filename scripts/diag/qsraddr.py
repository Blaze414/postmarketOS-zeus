#!/usr/bin/env python3
"""Locate QShrink log descriptors in the ADSP image and print their addresses.

Log call sites are 12-byte descriptors, { ssid << 16 | line, ss_mask, hash },
laid out in the order the source file declares them. A hashed message carries
no text, but knowing where its descriptor lives gives something to look for
xrefs to - which is what names the function that logged it.

    qsraddr.py <adsp.mbn> <ssid> <line> <hash>
    qsraddr.py <adsp.mbn> --batch ssid:line:hash [...]
"""
import struct
import sys


def segments(data):
    assert data[:4] == b"\x7fELF", "not an ELF"
    e_phoff, = struct.unpack_from("<I", data, 0x1C)
    e_phentsize, e_phnum = struct.unpack_from("<HH", data, 0x2A)
    segs = []
    for i in range(e_phnum):
        o = e_phoff + i * e_phentsize
        vaddr, = struct.unpack_from("<I", data, o + 0x08)
        off, = struct.unpack_from("<I", data, o + 0x04)
        filesz, = struct.unpack_from("<I", data, o + 0x10)
        if filesz:
            segs.append((vaddr, off, filesz))
    return segs


def o2v(segs, off):
    for vaddr, foff, size in segs:
        if foff <= off < foff + size:
            return vaddr + (off - foff)
    return None


def find(data, segs, ssid, line, want):
    key = struct.pack("<I", (ssid << 16) | line)
    hits = []
    start = 0
    while True:
        i = data.find(key, start)
        if i < 0:
            break
        start = i + 4
        if i % 4:
            continue
        h, = struct.unpack_from("<I", data, i + 8)
        if h == want:
            hits.append((i, o2v(segs, i)))
    return hits


def main():
    data = open(sys.argv[1], "rb").read()
    segs = segments(data)

    if sys.argv[2] == "--batch":
        specs = sys.argv[3:]
    else:
        specs = [":".join(sys.argv[2:5])]

    for spec in specs:
        ssid, line, h = spec.split(":")
        ssid, line, h = int(ssid), int(line), int(h, 16)
        hits = find(data, segs, ssid, line, h)
        if not hits:
            print(f"{h:08x} line {line}: not found")
        for off, va in hits:
            print(f"{h:08x} line {line}: file 0x{off:x}  vaddr 0x{va:08x}")


if __name__ == "__main__":
    if len(sys.argv) < 4:
        sys.exit(__doc__)
    main()
