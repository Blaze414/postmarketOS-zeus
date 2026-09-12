# Linux build host for the zeus mainline port, for use on macOS.
#
# Two jobs run in here:
#   1. Kernel/dts compilation  - needs nothing special, runs unprivileged.
#   2. pmbootstrap image build - needs loop devices, so needs --privileged.
#
# Flashing does NOT happen in here. Docker Desktop on macOS cannot pass through
# USB, so fastboot runs natively on the Mac against the images this container drops
# into ./out. See scripts/dev.sh.
FROM debian:trixie

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
      git make gcc bc bison flex libssl-dev libelf-dev \
      gcc-aarch64-linux-gnu \
      device-tree-compiler \
      python3 python3-venv pipx python3-libfdt \
      android-sdk-libsparse-utils \
      ca-certificates xz-utils file kmod sudo \
      # pmbootstrap host requirements: loop/partition handling, ps, filesystems
      multipath-tools procps util-linux e2fsprogs f2fs-tools btrfs-progs \
      dosfstools parted openssl android-sdk-libsparse-utils rsync \
    && rm -rf /var/lib/apt/lists/*

# pmbootstrap refuses to run as root, so give it a real user.
RUN useradd -m -s /bin/bash pmos && echo 'pmos ALL=(ALL) NOPASSWD:ALL' > /etc/sudoers.d/pmos
USER pmos
WORKDIR /work

# pmbootstrap is NOT installable from PyPI - every release there is yanked
# (checked to 2.1.0). GitLab is the only source. Pin a release branch rather
# than master so a container rebuild does not silently change the tool.
RUN pipx install "git+https://gitlab.postmarketos.org/postmarketOS/pmbootstrap.git@3.10.x" 
ENV PATH="/home/pmos/.local/bin:${PATH}"
ENV ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-

CMD ["/bin/bash"]
