#!/usr/bin/env python3
"""Replace every devicetree copy inside an Android boot image (header v0-v2).

An sm8450 pmOS boot image carries the FDT twice:

  * appended to the gzipped kernel (Image.gz-dtb), inside the kernel region;
  * in the header-v2 `dtb` region, described by dtb_size at offset 1648.

ABL passes the v2 region to the kernel, so patching only the appended copy
changes nothing observable - which is exactly the trap this script exists to
avoid. Both are replaced. Region sizes change, and every region after the header
page is page-aligned, so the image is rebuilt rather than patched in place.
"""
import struct
import sys

FDT_MAGIC = bytes.fromhex('d00dfeed')
OFF_KERNEL_SIZE = 8
OFF_PAGE_SIZE = 36
OFF_HEADER_VERSION = 40
OFF_RECOVERY_DTBO_SIZE = 1632
OFF_DTB_SIZE = 1648


def fdt_totalsize(blob, at):
    return struct.unpack_from('>I', blob, at + 4)[0]     # FDT header is big-endian


def split_appended(kernel_region):
    """Split a kernel region into (kernel, appended dtb). dtb may be None."""
    i = kernel_region.rfind(FDT_MAGIC)
    if i < 0:
        return kernel_region, None
    size = fdt_totalsize(kernel_region, i)
    if i + size != len(kernel_region):
        # a stray magic byte sequence inside the compressed kernel, not a real dtb
        return kernel_region, None
    return kernel_region[:i], kernel_region[i:]


def splice(boot, new_dtb):
    if boot[:8] != b'ANDROID!':
        raise SystemExit('!! not an Android boot image')
    ks, _ka, rs, _ra, ss, _sa, _tags, ps = struct.unpack_from('<8I', boot, OFF_KERNEL_SIZE)
    hv = struct.unpack_from('<I', boot, OFF_HEADER_VERSION)[0]

    def pad(n):
        return (n + ps - 1) // ps * ps

    sizes = [ks, rs, ss]
    if hv >= 1:
        sizes.append(struct.unpack_from('<I', boot, OFF_RECOVERY_DTBO_SIZE)[0])
    if hv >= 2:
        sizes.append(struct.unpack_from('<I', boot, OFF_DTB_SIZE)[0])

    off = ps
    regions = []
    for size in sizes:
        regions.append(boot[off:off + size])
        off += pad(size)

    replaced = []

    kern, appended = split_appended(regions[0])
    if appended is not None:
        regions[0] = kern + new_dtb
        replaced.append('appended (%d -> %d)' % (len(appended), len(new_dtb)))

    if hv >= 2 and sizes[4]:
        if regions[4][:4] != FDT_MAGIC:
            raise SystemExit('!! v2 dtb region does not start with an FDT')
        replaced.append('v2 region (%d -> %d)' % (sizes[4], len(new_dtb)))
        regions[4] = new_dtb

    if not replaced:
        raise SystemExit('!! found no devicetree to replace')

    out = bytearray(boot[:ps])
    struct.pack_into('<I', out, OFF_KERNEL_SIZE, len(regions[0]))
    if hv >= 2 and sizes[4]:
        struct.pack_into('<I', out, OFF_DTB_SIZE, len(regions[4]))
    for r in regions:
        out += r + b'\0' * (pad(len(r)) - len(r))
    out += boot[off:]
    return bytes(out), replaced


def dtbs_in(img):
    """Every dtb an image would hand a bootloader, for verification."""
    boot = open(img, 'rb').read()
    ks, _, rs, _, ss, _, _, ps = struct.unpack_from('<8I', boot, OFF_KERNEL_SIZE)
    hv = struct.unpack_from('<I', boot, OFF_HEADER_VERSION)[0]
    pad = lambda n: (n + ps - 1) // ps * ps
    found = {}
    _, appended = split_appended(boot[ps:ps + ks])
    if appended:
        found['appended'] = appended
    if hv >= 2:
        dsz = struct.unpack_from('<I', boot, OFF_DTB_SIZE)[0]
        rdo = struct.unpack_from('<I', boot, OFF_RECOVERY_DTBO_SIZE)[0] if hv >= 1 else 0
        off = ps + pad(ks) + pad(rs) + pad(ss) + pad(rdo)
        if dsz:
            found['v2'] = boot[off:off + dsz]
    return found


def main():
    img, dtb, dst = sys.argv[1], sys.argv[2], sys.argv[3]
    new = open(dtb, 'rb').read()
    if new[:4] != FDT_MAGIC:
        raise SystemExit('!! %s is not a dtb' % dtb)
    out, replaced = splice(open(img, 'rb').read(), new)
    open(dst, 'wb').write(out)
    print('replaced: ' + ', '.join(replaced))

    # every copy the bootloader could pick must be the dtb we asked for
    back = dtbs_in(dst)
    for where, blob in back.items():
        assert blob == new, 'round-trip mismatch in %s copy' % where
    print('ok: %d dtb cop%s verified (%s)'
          % (len(back), 'y' if len(back) == 1 else 'ies', ', '.join(back)))


if __name__ == '__main__':
    main()
