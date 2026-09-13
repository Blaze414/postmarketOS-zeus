#!/usr/bin/env python3
"""Flip a built dtb between the GENI SPI controller and the bitbanged twin.

Both describe the same touchscreen on the same four pins, so exactly one may be
enabled - otherwise they fight over the pinmux. Doing this to the compiled dtb
rather than the source means switching costs a splice, not a kernel rebuild.

  select-spi.py <in.dtb> <out.dtb> geni|bitbang
"""
import subprocess
import sys

GENI = '/soc@0/geniqup@9c0000/spi@990000'
BITBANG = '/spi-gpio'


def set_status(dtb, path, value):
    subprocess.run(['fdtput', '-t', 's', dtb, path, 'status', value], check=True)


def get_status(dtb, path):
    out = subprocess.run(['fdtget', '-t', 's', dtb, path, 'status'],
                         check=True, capture_output=True, text=True)
    return out.stdout.strip()


def main():
    src, dst, mode = sys.argv[1], sys.argv[2], sys.argv[3]
    if mode not in ('geni', 'bitbang'):
        raise SystemExit('!! mode must be geni or bitbang')
    with open(src, 'rb') as f:
        open(dst, 'wb').write(f.read())

    set_status(dst, GENI, 'okay' if mode == 'geni' else 'disabled')
    set_status(dst, BITBANG, 'okay' if mode == 'bitbang' else 'disabled')

    geni, bit = get_status(dst, GENI), get_status(dst, BITBANG)
    assert (geni == 'okay') != (bit == 'okay'), \
        'exactly one bus must be enabled, got geni=%s bitbang=%s' % (geni, bit)
    print('%s: spi@990000=%s  spi-gpio=%s' % (mode, geni, bit))


if __name__ == '__main__':
    main()
