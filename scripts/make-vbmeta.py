#!/usr/bin/env python3
"""Generate an empty AVB vbmeta image with verification disabled.

The zeus bootloader reports "Verity mode: true" and refuses to boot an unsigned
kernel - it rejects the image outright rather than attempting it (slot-retry-count
stays at its maximum). Flashing a vbmeta whose header carries the disable flags
turns AVB off so an unsigned pmOS boot.img is accepted.

Layout is AvbVBMetaImageHeader from AOSP libavb (avb_vbmeta_image.h): 256 bytes,
all fields big-endian. Everything is zero except the magic, the required libavb
version and the flags.

flags: 1 = HASHTREE_DISABLED, 2 = VERIFICATION_DISABLED -> 3 = both.
"""
import struct
import sys

FLAGS_HASHTREE_DISABLED = 1
FLAGS_VERIFICATION_DISABLED = 2


def make_vbmeta(flags: int = FLAGS_HASHTREE_DISABLED | FLAGS_VERIFICATION_DISABLED) -> bytes:
    header = b"".join([
        b"AVB0",                    # magic
        struct.pack(">I", 1),       # required_libavb_version_major
        struct.pack(">I", 0),       # required_libavb_version_minor
        struct.pack(">Q", 0),       # authentication_data_block_size
        struct.pack(">Q", 0),       # auxiliary_data_block_size
        struct.pack(">I", 0),       # algorithm_type = NONE
        struct.pack(">Q", 0),       # hash_offset
        struct.pack(">Q", 0),       # hash_size
        struct.pack(">Q", 0),       # signature_offset
        struct.pack(">Q", 0),       # signature_size
        struct.pack(">Q", 0),       # public_key_offset
        struct.pack(">Q", 0),       # public_key_size
        struct.pack(">Q", 0),       # public_key_metadata_offset
        struct.pack(">Q", 0),       # public_key_metadata_size
        struct.pack(">Q", 0),       # descriptors_offset
        struct.pack(">Q", 0),       # descriptors_size
        struct.pack(">Q", 0),       # rollback_index
        struct.pack(">I", flags),   # flags
        struct.pack(">I", 0),       # rollback_index_location
        b"avbtool 1.0.0\0".ljust(48, b"\0"),   # release_string[48]
        b"\0" * 80,                 # reserved[80]
    ])
    assert len(header) == 256, len(header)
    # Pad to 4096 so it writes cleanly to a flash page.
    return header + b"\0" * (4096 - len(header))


if __name__ == "__main__":
    out = sys.argv[1] if len(sys.argv) > 1 else "vbmeta-disabled.img"
    data = make_vbmeta()
    with open(out, "wb") as f:
        f.write(data)
    print(f"{out}: {len(data)} bytes, magic={data[:4].decode()}, flags={data[123]}")
