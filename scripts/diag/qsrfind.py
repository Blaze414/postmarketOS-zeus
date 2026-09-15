#!/usr/bin/env python3
"""Resolve QShrink-hashed ADSP messages against the firmware image.

The ADSP's log call sites are 16-byte descriptors laid down in the order the
source file declares them:

    { ssid << 16 | line, ss_mask, format_ptr_or_hash, 0 }

QShrink replaces the format pointer with a hash, so a hashed message carries
no text of its own. Its neighbours in the same file often do still carry real
pointers, though - and the file name is one of the strings they point at. So:
find the descriptor by (ssid, line, hash), then walk outwards printing every
descriptor whose third word looks like a pointer into a string section.

    qsrfind.py <adsp.mbn> <ssid> <line> [hash] [--window N]
"""
import re
import struct
import sys


def load_segments(data):
    """Return [(vaddr, offset, filesz)] from the ELF program headers."""
    assert data[:4] == b"\x7fELF", "not an ELF"
    is64 = data[4] == 2
    if not is64:
        e_phoff, = struct.unpack_from("<I", data, 0x1C)
        e_phentsize, e_phnum = struct.unpack_from("<HH", data, 0x2A)
        fmt, voff, ooff, soff = "<I", 0x08, 0x04, 0x10
    else:
        e_phoff, = struct.unpack_from("<Q", data, 0x20)
        e_phentsize, e_phnum = struct.unpack_from("<HH", data, 0x36)
        fmt, voff, ooff, soff = "<Q", 0x10, 0x08, 0x20

    segs = []
    for i in range(e_phnum):
        p = e_phoff + i * e_phentsize
        vaddr, = struct.unpack_from(fmt, data, p + voff)
        off, = struct.unpack_from(fmt, data, p + ooff)
        filesz, = struct.unpack_from(fmt, data, p + soff)
        if filesz:
            segs.append((vaddr, off, filesz))
    return segs


def v2o(segs, vaddr):
    for base, off, size in segs:
        if base <= vaddr < base + size:
            return off + (vaddr - base)
    return None


def cstr(data, off, limit=200):
    end = data.find(b"\0", off, off + limit)
    if end < 0:
        return None
    s = data[off:end]
    if not s or not all(32 <= c < 127 or c in (9, 10) for c in s):
        return None
    return s.decode()


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    window = 24
    for a in sys.argv[1:]:
        if a.startswith("--window"):
            window = int(a.split("=")[1])

    path, ssid, line = args[0], int(args[1]), int(args[2])
    want_hash = int(args[3], 16) if len(args) > 3 else None

    data = open(path, "rb").read()
    segs = load_segments(data)
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
        third, = struct.unpack_from("<I", data, i + 8)
        if want_hash is None or third == want_hash:
            hits.append(i)

    if not hits:
        print("no descriptor found")
        return

    for h in hits:
        print(f"=== descriptor at file offset 0x{h:x} ===")
        for n in range(-window, window + 1):
            off = h + n * 16
            if off < 0 or off + 16 > len(data):
                continue
            w0, mask, ptr, tail = struct.unpack_from("<IIII", data, off)
            if (w0 >> 16) != ssid or tail != 0:
                continue
            t = v2o(segs, ptr)
            s = cstr(data, t) if t is not None else None
            mark = " <<<" if off == h else ""
            if s:
                print(f"  line {w0 & 0xFFFF:5d}  {s!r}{mark}")
            else:
                print(f"  line {w0 & 0xFFFF:5d}  hash={ptr:08x}{mark}")


if __name__ == "__main__":
    if len(sys.argv) < 4:
        sys.exit(__doc__)
    main()
