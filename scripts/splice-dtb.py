#!/usr/bin/env python3
"""Replace the dtb appended to the kernel inside an Android boot image (v0-v2).

pmbootstrap ships sm8450 kernels as Image.gz-dtb: the FDT is concatenated onto
the gzipped kernel and the pair is stored in the kernel region. Swapping the dtb
therefore changes kernel_size, which shifts every following (page-aligned)
region, so the header has to be rewritten rather than patched in place.
"""
import struct, sys

FDT_MAGIC = bytes.fromhex('d00dfeed')


def split_kernel(blob):
    """Return (kernel, old_dtb). The dtb is the last FDT in the blob."""
    i = blob.rfind(FDT_MAGIC)
    if i < 0:
        raise SystemExit('!! no FDT appended to the kernel')
    size = struct.unpack_from('>I', blob, i + 4)[0]      # totalsize, big-endian
    if i + size > len(blob):
        raise SystemExit('!! FDT at %#x claims %d bytes, past end' % (i, size))
    return blob[:i], blob[i:i + size]


def splice(boot, new_dtb):
    if boot[:8] != b'ANDROID!':
        raise SystemExit('!! not an Android boot image')
    ks, ka, rs, ra, ss, sa, tags, ps = struct.unpack_from('<8I', boot, 8)

    def pad(n):
        return (n + ps - 1) // ps * ps

    kern, old = split_kernel(boot[ps:ps + ks])
    # regions in order after the header page
    off = ps
    parts = []
    for size in (ks, rs, ss):
        parts.append(boot[off:off + size])
        off += pad(size)
    tail = boot[off:]                                    # v1/v2 extra regions

    parts[0] = kern + new_dtb
    new_ks = len(parts[0])

    out = bytearray(boot[:ps])
    struct.pack_into('<I', out, 8, new_ks)
    for p in parts:
        out += p + b'\0' * (pad(len(p)) - len(p))
    out += tail
    return bytes(out), len(old), len(new_dtb)


def main():
    img, dtb, dst = sys.argv[1], sys.argv[2], sys.argv[3]
    boot = open(img, 'rb').read()
    new = open(dtb, 'rb').read()
    if new[:4] != FDT_MAGIC:
        raise SystemExit('!! %s is not a dtb' % dtb)
    out, oldsz, newsz = splice(boot, new)
    open(dst, 'wb').write(out)
    print('dtb %d -> %d bytes, image %d -> %d' % (oldsz, newsz, len(boot), len(out)))

    # round-trip: the image we just wrote must hand back the dtb we put in
    back = open(dst, 'rb').read()
    ps = struct.unpack_from('<I', back, 36)[0]
    ks = struct.unpack_from('<I', back, 8)[0]
    assert split_kernel(back[ps:ps + ks])[1] == new, 'round-trip mismatch'
    print('ok: round-trip verified')


if __name__ == '__main__':
    main()
