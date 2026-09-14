#!/usr/bin/env python3
# Minimal diag client for linux-msm diag-router (-s 127.0.0.1:2500).
# Enables all F3 message masks and prints extended (0x79) messages;
# QSR (0x92/0x99, hashed format strings) are printed as hash + args.
import socket, struct, sys, re, time

def crc16(data):
    crc = 0xFFFF
    for b in data:
        crc ^= b
        for _ in range(8):
            crc = (crc >> 1) ^ 0x8408 if crc & 1 else crc >> 1
    return crc ^ 0xFFFF

def hdlc(payload):
    raw = payload + struct.pack("<H", crc16(payload))
    out = bytearray()
    for b in raw:
        if b in (0x7E, 0x7D):
            out += bytes([0x7D, b ^ 0x20])
        else:
            out.append(b)
    return bytes(out) + b"\x7e"

def unhdlc(frame):
    out, esc = bytearray(), False
    for b in frame:
        if esc:
            out.append(b ^ 0x20); esc = False
        elif b == 0x7D:
            esc = True
        else:
            out.append(b)
    return bytes(out[:-2]) if len(out) >= 2 else b""

def fmt(s, args):
    it = iter(args)
    def rep(m):
        try:
            v = next(it)
        except StopIteration:
            return m.group(0)
        c = m.group(0)[-1]
        if c in "xXp": return "%x" % v
        if c == "s": return "<str@%x>" % v
        if c in "di": return str(struct.unpack("<i", struct.pack("<I", v))[0])
        return str(v)
    return re.sub(r"%[-#0 +]*\d*(?:\.\d+)?(?:hh|h|ll|l|z)?[diouxXpcs]", rep, s)

def handle(pkt, out):
    if not pkt: return
    c = pkt[0]
    if c == 0x79 and len(pkt) >= 20:
        _, _, nargs, _, ts, line, ssid, mask = struct.unpack_from("<BBBBQHHI", pkt, 0)
        args = struct.unpack_from("<%dI" % nargs, pkt, 20)
        rest = pkt[20 + 4 * nargs:].split(b"\0")
        f = rest[0].decode(errors="replace"); fn = rest[1].decode(errors="replace") if len(rest) > 1 else ""
        out.write("[ssid %d] %s:%d %s\n" % (ssid, fn, line, fmt(f, args)))
    elif c in (0x92, 0x99) and len(pkt) >= 24:
        _, _, nargs, _, ts, line, ssid, mask, h = struct.unpack_from("<BBBBQHHII", pkt, 0)
        args = struct.unpack_from("<%dI" % min(nargs, (len(pkt) - 24) // 4), pkt, 24)
        out.write("[ssid %d QSR 0x%02x] hash=%08x line=%d args=%s\n" % (ssid, c, h, line, [hex(a) for a in args]))
    out.flush()

srv = socket.socket(); srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
srv.bind(("127.0.0.1", 2500)); srv.listen(1)
print("waiting for diag-router", flush=True)
conn, _ = srv.accept()
conn.sendall(hdlc(bytes([0x7D, 0x05, 0x00]) + struct.pack("<I", 0xFFFFFFFF)))
print("masks sent", flush=True)
out = open(sys.argv[1], "w") if len(sys.argv) > 1 else sys.stdout
buf = b""
while True:
    d = conn.recv(65536)
    if not d: break
    buf += d
    while b"\x7e" in buf:
        frame, buf = buf.split(b"\x7e", 1)
        handle(unhdlc(frame + b"\x7e"[:0]), out)
