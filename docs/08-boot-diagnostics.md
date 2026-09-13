# Boot diagnostics: what the slot counter says, and why ramoops cannot help

Two Droidian flash attempts came back dark with no log, and the guesswork about
why was getting expensive. This is what actually measuring it produced.

## ABL accepts the Halium image. The kernel dies.

`slot-retry-count` answers this, and it has to be read while still in fastboot,
immediately after a failed attempt:

```bash
fastboot getvar slot-retry-count:a
```

Baseline 6. After one failed Halium boot: 2. Four decrements inside the 33
seconds before ABL gave up and fell back to fastboot - four attempts, about
eight seconds each. ABL only decrements once it has handed control to the
kernel; during the mainline port an AVB rejection left the counter at maximum.

So the devicetree, the header layout and the signature are all accepted. The
image is fine. The kernel starts and dies, four times over.

That also explains the empty mtdoops log from the previous attempt: mtdoops
rides on block2mtd, which needs the UFS stack, and nothing gets close.

## ramoops is not a usable channel on this device

It should have been the answer. It initialises from `reserved_mem` in early
boot, Xiaomi already reserves 4 MB at `0xa7000000`, and both kernels have
`CONFIG_PSTORE_RAM` and `CONFIG_PSTORE_CONSOLE`.

Getting it configured correctly took three corrections:

| Property | Verdict |
|---|---|
| `ecc-size = <16>` | **Remove.** It shrinks `buffer_size` for a parity footer, so a record written by the no-ECC downstream kernel reads back as an oversized, invalid buffer and is zapped before it can be read. Two kernels can only share the region if the zone geometry matches byte for byte. |
| `no-map` | **Keep.** Without it the region joins the linear map as ordinary cached memory, and `persistent_ram` writes with plain `memcpy` and no cache maintenance - the console sits in CPU cache and never reaches DRAM before the reset. |
| `record-size` | **Do not add.** ramoops lays out dmesg records first, *then* console. Adding records shifts the console zone, so the downstream kernel's log would no longer be where mainline looks for it. (2M console + 2M pmsg also already fills the region.) |

With all three right - `nomap`, `ecc: 0`, geometry identical to stock - the
region still comes up empty on the next boot. Tested with a console canary
written to `/dev/kmsg`, a `/dev/pmsg0` canary, across both a clean reboot and a
genuine `sysrq-c` panic. Every one lost, with no "found existing invalid buffer"
message, which means the region reads back as zero rather than corrupt.

**XBL scrubs DRAM on the way back up.** ramoops cannot carry anything across a
reset on zeus, and no amount of devicetree work changes that. The node is left
in its correct form, but it is inert. Do not spend more time here - the next
real diagnostic channel is a UART console, which needs a debug cable.

## The device runs out of boot credits on its own

Found while chasing the above, and unrelated to Droidian.

postmarketOS never marked the slot successful: `qbootctl` was installed, its
init script was present, and it was in no runlevel. `qbootctl-openrc` does not
exist in this pmaports branch - the init script ships with `qbootctl` itself -
so the `openrc` subpackage depending on it was never going to work.

The init script's own comment describes the symptom exactly: without it, "after
~7 reboots A/B devices automatically switch to the inactive slot causing a lot
of confusion and usually a soft-bricked device".

That is precisely what was happening. ABL decrements the retry counter on every
boot, nothing ever resets it, and around the seventh the device declares the
slot unbootable and drops into fastboot by itself. It looks exactly like a crash
and is not one. Fixed in the `openrc` subpackage's post-install; verified
`Successful : 1` now survives a reboot.

**This matters when reading any of the numbers above.** A decrement means ABL
handed off, nothing more - a perfectly good boot decrements too. Only the
*rate* distinguishes the cases: four decrements in 33 seconds is four failed
attempts; one decrement per boot is normal.

## Working without the touchscreen

Neither SSH nor a reboot to fastboot needed the user, once set up.

- The username is **`pmos`**, not `user` - set by `pmbootstrap config user pmos`
  in `scripts/pmb.sh`. The password was right all along.
- `doas`, not `sudo`, and it wants a tty.
- Flashing needs no fastboot: with root on the device,
  `dd if=boot.img of=/dev/disk/by-partlabel/boot_a bs=1M conv=fsync` works from
  the running system, and it is checksum-verifiable.
- `reboot bootloader` does **not** reach fastboot. busybox drops the argument,
  and the `reboot(2)` RESTART2 call is ignored because mainline has no
  reboot-mode handler wired to IMEM. Adding a `syscon-reboot-mode` node to the
  IMEM syscon looked right and made the kernel unbootable - reverted, untested
  further. When the slot runs out of retries the device reaches fastboot by
  itself anyway.

## Tooling

`scripts/splice-dtb.py` swaps the devicetree inside a boot image without a
pmbootstrap run. An sm8450 pmOS boot image carries the FDT **twice**: appended
to the gzipped kernel, and in the header-v2 `dtb` region. ABL uses the v2 region,
so patching only the appended copy changes nothing observable - which cost a
flash cycle to discover. The script replaces both and verifies by reading them
back out of the image it wrote.
