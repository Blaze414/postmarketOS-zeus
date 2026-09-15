#!/usr/bin/env python3
"""Rewrite the filesystem UUIDs in an Android boot image's kernel cmdline.

pmbootstrap stamps the boot image with the UUIDs of the rootfs image it built
in the same run. Flashing that boot image onto a phone installed from an
earlier build leaves the initramfs searching for a filesystem that is not
there, and the phone falls back to fastboot - which looks exactly like a
kernel that failed to boot.

Both UUIDs are the same length as what they replace, so the cmdline field is
edited in place and nothing else in the image moves.

    bootimg-uuid.py in.img out.img --root <uuid> [--boot <uuid>]

Read the UUIDs off the phone with:  cat /proc/cmdline
"""
import argparse
import re
import sys

# Android boot image header v0-v3: magic, then the cmdline at a fixed offset.
CMDLINE_OFF = 64
CMDLINE_LEN = 512
UUID_RE = r"[0-9a-fA-F-]{36}"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("dst")
    ap.add_argument("--root", required=True, help="pmos_root_uuid to write")
    ap.add_argument("--boot", help="pmos_boot_uuid to write")
    args = ap.parse_args()

    data = bytearray(open(args.src, "rb").read())
    if data[:8] != b"ANDROID!":
        sys.exit(f"{args.src}: not an Android boot image")

    old = data[CMDLINE_OFF:CMDLINE_OFF + CMDLINE_LEN].split(b"\0")[0].decode()
    new = old

    for key, val in (("pmos_root_uuid", args.root), ("pmos_boot_uuid", args.boot)):
        if not val:
            continue
        if not re.fullmatch(UUID_RE, val):
            sys.exit(f"{val!r} is not a UUID")
        new, n = re.subn(rf"{key}={UUID_RE}", f"{key}={val}", new)
        if n != 1:
            sys.exit(f"{key} appears {n} times in the cmdline, expected once")

    if len(new) != len(old):
        sys.exit("cmdline changed length; refusing to write")

    data[CMDLINE_OFF:CMDLINE_OFF + len(new)] = new.encode()
    open(args.dst, "wb").write(data)

    print(f"  was: {old}")
    print(f"  now: {new}")


if __name__ == "__main__":
    main()
