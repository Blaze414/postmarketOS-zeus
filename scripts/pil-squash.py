#!/usr/bin/env python3
"""Merge Qualcomm split firmware (.mdt + .bNN) into a single .mbn.

Android ships remoteproc firmware as an ELF header file (.mdt) plus one file per
loadable segment (.b00, .b01, ...). Mainline's remoteproc loader wants them
merged into one .mbn. This is the same job as the `pil-squasher` tool.

Each program header's p_offset says where its segment belongs in the merged
file; segments with p_filesz == 0 have no .bNN file.
"""
import struct, sys
from pathlib import Path


def squash(mdt: Path, out: Path) -> None:
    data = mdt.read_bytes()
    if data[:4] != b"\x7fELF":
        raise SystemExit(f"{mdt}: not an ELF")

    is64 = data[4] == 2
    if is64:
        e_phoff, e_phentsize, e_phnum = (
            struct.unpack_from("<Q", data, 0x20)[0],
            struct.unpack_from("<H", data, 0x36)[0],
            struct.unpack_from("<H", data, 0x38)[0],
        )
    else:
        e_phoff, e_phentsize, e_phnum = (
            struct.unpack_from("<I", data, 0x1C)[0],
            struct.unpack_from("<H", data, 0x2A)[0],
            struct.unpack_from("<H", data, 0x2C)[0],
        )

    # The .mdt's own headers form the start of the merged image.
    blob = bytearray(data)
    written = 0
    for i in range(e_phnum):
        off = e_phoff + i * e_phentsize
        if is64:
            p_offset = struct.unpack_from("<Q", data, off + 0x08)[0]
            p_filesz = struct.unpack_from("<Q", data, off + 0x20)[0]
        else:
            p_offset = struct.unpack_from("<I", data, off + 0x04)[0]
            p_filesz = struct.unpack_from("<I", data, off + 0x10)[0]
        if not p_filesz:
            continue
        seg = mdt.with_suffix(f".b{i:02d}")
        if not seg.exists():
            print(f"  !! {mdt.stem}: missing {seg.name}, skipping", file=sys.stderr)
            continue
        payload = seg.read_bytes()
        end = p_offset + len(payload)
        if end > len(blob):
            blob.extend(b"\x00" * (end - len(blob)))
        blob[p_offset:end] = payload
        written += 1

    out.write_bytes(bytes(blob))
    print(f"  {out.name}: {len(blob):,} bytes from {written} segments")


def main() -> None:
    src, dst = Path(sys.argv[1]), Path(sys.argv[2])
    dst.mkdir(parents=True, exist_ok=True)
    mdts = sorted(src.glob("*.mdt"))
    if not mdts:
        raise SystemExit(f"no .mdt files in {src}")
    for mdt in mdts:
        squash(mdt, dst / (mdt.stem + ".mbn"))


if __name__ == "__main__":
    main()
