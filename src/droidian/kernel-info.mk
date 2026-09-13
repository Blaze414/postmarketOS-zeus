########################################################################
# Kernel settings - Xiaomi 12 Pro (zeus)
#
# Offsets, page size and header version are not guesses: they were read
# from this device and verified by flashing a working boot image during
# the mainline port. See src/pmaports/device-xiaomi-zeus/deviceinfo.
########################################################################

VARIANT = android
KERNEL_BASE_VERSION = 5.10.256

# firmware_class.path points at the vendor firmware mount so the FTS
# touchscreen and the remoteprocs can find their blobs.
KERNEL_BOOTIMAGE_CMDLINE = androidboot.hardware=qcom androidboot.console=ttyMSM0 \
	msm_rtb.filter=0x237 service_locator.enable=1 swiotlb=noforce \
	firmware_class.path=/vendor/firmware_mnt/image loop.max_part=7 \
	cgroup.memory=nokmem,nosocket console=tty0 droidian.lvm.prefer \
	systemd.unified_cgroup_hierarchy=0

DEVICE_VENDOR = xiaomi
DEVICE_MODEL = zeus
DEVICE_FULL_NAME = Xiaomi 12 Pro

# Starting point: Qualcomm's GKI config plus the waipio vendor fragment.
# waipio_le.config (Qualcomm's Linux Embedded variant) is the other candidate
# and may need less Android-specific unpicking.
KERNEL_DEFCONFIG = zeus_droidian_defconfig

KERNEL_IMAGE_WITH_DTB = 1
KERNEL_IMAGE_DTB = arch/arm64/boot/dts/vendor/qcom/zeus-sm8450.dtb

# zeus boots base dtb + dtbo overlay - the mechanism the mainline port had to
# erase. Here we want it back.
KERNEL_IMAGE_WITH_DTB_OVERLAY = 1
KERNEL_IMAGE_DTB_OVERLAY = arch/arm64/boot/dts/vendor/qcom/zeus-sm8450-pm8008-overlay.dtbo
KERNEL_IMAGE_WITH_DTB_OVERLAY_IN_KERNEL = 0

# Verified against the device: fastboot getvar and a booting boot.img.
KERNEL_BOOTIMAGE_PAGE_SIZE = 4096
KERNEL_BOOTIMAGE_BASE_OFFSET = 0x00000000
KERNEL_BOOTIMAGE_KERNEL_OFFSET = 0x00008000
KERNEL_BOOTIMAGE_INITRAMFS_OFFSET = 0x01000000
KERNEL_BOOTIMAGE_SECONDIMAGE_OFFSET = 0x00000000
KERNEL_BOOTIMAGE_TAGS_OFFSET = 0x00000100
KERNEL_BOOTIMAGE_DTB_OFFSET = 0x01f00000
KERNEL_BOOTIMAGE_VERSION = 2

########################################################################
# Android verified boot
########################################################################
# zeus reports "Verity mode: true" and rejects unsigned kernels outright,
# so an empty vbmeta is mandatory - confirmed during the mainline port,
# where it had to be flashed to BOTH slots.
DEVICE_VBMETA_REQUIRED = 1
DEVICE_VBMETA_IS_SAMSUNG = 0

########################################################################
# Flashing
########################################################################
FLASH_ENABLED = 1
# zeus is A/B (slot-count 2, current-slot a), NOT a-only.
FLASH_IS_AONLY = 0
FLASH_IS_LEGACY_DEVICE = 0
FLASH_INFO_MANUFACTURER = Xiaomi
FLASH_INFO_MODEL = 2201122G
FLASH_INFO_CPU = SM8450
FLASH_INFO_DEVICE_IDS = zeus

########################################################################
# Build settings
########################################################################
BUILD_CROSS = 1
BUILD_TRIPLET = aarch64-linux-android-
BUILD_CLANG_TRIPLET = aarch64-linux-gnu-
# msm-kernel 5.10 is a clang build; gcc will not do.
BUILD_CC = clang
KERNEL_ARCH = arm64
KERNEL_BUILD_TARGET = Image.gz
DEB_BUILD_ON = amd64
DEB_BUILD_FOR = arm64
