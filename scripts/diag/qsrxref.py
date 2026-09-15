#!/usr/bin/env python3
"""Find the code that references a given address in a Hexagon image.

Hexagon builds a 32-bit constant from a constant-extender instruction plus the
instruction that follows it, so the address never appears as four contiguous
bytes and a plain search finds nothing. The extender does carry imm[31:6],
though, which is enough to locate candidates to within 64 bytes:

    0000 | imm[31:20] (bits 27-16) | parse (bits 15-14) | imm[19:6] (bits 13-0)

    qsrxref.py <adsp.mbn> <vaddr> [...]
"""
import struct
import sys


def segments(data):
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


def ext_words(addr):
    """Every plausible encoding of immext(##addr), over the parse bits."""
    hi = (addr >> 20) & 0xFFF
    lo = (addr >> 6) & 0x3FFF
    return [(hi << 16) | (parse << 14) | lo for parse in (0b01, 0b10, 0b11)]


def main():
    data = open(sys.argv[1], "rb").read()
    segs = segments(data)

    for arg in sys.argv[2:]:
        addr = int(arg, 16)
        print(f"=== references to 0x{addr:08x} ===")
        found = 0
        for w in ext_words(addr):
            pat = struct.pack("<I", w)
            start = 0
            while True:
                i = data.find(pat, start)
                if i < 0:
                    break
                start = i + 4
                if i % 4:
                    continue
                va = o2v(segs, i)
                if va is None:
                    continue
                print(f"  immext at file 0x{i:x}  vaddr 0x{va:08x}")
                found += 1
        if not found:
            print("  none")


if __name__ == "__main__":
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    main()
