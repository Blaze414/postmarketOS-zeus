# Build AudioReach graphservices (GSL) for postmarketOS, without autotools.
#
# configure.ac is written around Android: it wants cutils, libion, the PD
# notifier and Qualcomm's ION shmem. Every one of those is optional, but
# untangling the AM_CONDITIONALs from outside an Android tree costs more than
# listing the files does - and this way the include set and the flag set are
# visible, which matters because the whole port hinges on them.
#
#   make GS=/path/to/audioreach-graphservices
#
# Shared memory comes from ar_osal_shmem_audio_pkt.c here, not from any of the
# tree's own backends: the virtual one hands the DSP malloc'd pages it cannot
# reach, and both Qualcomm backends want Android kernel headers.

GS ?= $(CURDIR)/gs
O  := $(GS)/ar_osal/src/linux
Q  := $(GS)/ar_osal/src/linux/qcom

CC      ?= gcc
# -w: the tree is full of Android-era warnings and is not ours to clean.
# __unused is a bionic spelling; _GNU_SOURCE is for pthread_setname_np.
# GCC 14 promoted incompatible-pointer-types to an error; this tree predates
# that and trips it in acdb_init_utility.c's ar_fmap() call.
# SESSION_ARRAY_SIZE is not defaulted anywhere - gpr/Makefile.am passes it on
# the command line, and gpr_drv.c sizes its packet pools with it.
CFLAGS  ?= -O2 -w -fPIC -D_GNU_SOURCE \
	   -include $(CURDIR)/ar_compat.h \
	   -I$(CURDIR) -I$(CURDIR)/../../src/kernel \
	   -DSESSION_ARRAY_SIZE=200 -DGSL_DEBUG_ENABLE \
	   -Wno-error=incompatible-pointer-types
LDLIBS  := -lpthread -ldl

# Every directory in the tree that holds headers, except the ar_utils variants
# meant for the DSP itself (hexagon/audioss) - those shadow the generic ones.
INCDIRS := $(shell find $(GS)/gpr $(GS)/acdb $(GS)/ar_osal $(GS)/ar_util \
		$(GS)/gsl $(GS)/spf $(GS)/public_headers -type d 2>/dev/null \
		| grep -vE "ar_utils/(hexagon|audioss)")
INC     := $(foreach d,$(INCDIRS),$(if $(wildcard $(d)/*.h),-I$(d)))

# ar_osal: the Linux backend, minus the three Android-only files.
#   ar_osal_log.c       - needs cutils' log/log.h (stubs.c provides ar_log)
#   ar_osal_signal2.c   - ALOGE, and unused; ar_osal_signal.c is the live one
#   ar_osal_shmem_phy.c - needs linux/msm_audio.h
#   ar_osal_shmem_virtual.c - replaced by ar_osal_shmem_audio_pkt.c
SRC := $(filter-out $(O)/ar_osal_log.c $(O)/ar_osal_signal2.c \
		$(O)/ar_osal_shmem_phy.c $(O)/ar_osal_shmem_virtual.c, \
		$(wildcard $(O)/*.c)) \
	ar_osal_shmem_audio_pkt.c \
	$(Q)/ar_osal_servreg.c \
	$(Q)/dyn_pd/ar_osal_dyn_pd.c \
	$(wildcard $(GS)/ar_util/src/*.c) \
	$(wildcard $(GS)/gpr/core/src/*.c) \
	$(wildcard $(GS)/gpr/core/src/hash_based/*.c) \
	$(GS)/gpr/ext/dynamic_allocation/src/gpr_dynamic_allocation.c \
	$(GS)/gpr/ext/logging/src/gpr_log_generic.c \
	$(GS)/gpr/ext/logging/stub_src/gpr_log_diag_stub.c \
	$(GS)/gpr/datalinks/gpr_lx/src/gpr_lx.c \
	$(GS)/gpr/platform/linux/gpr_init_lx_wrapper.c \
	$(wildcard $(GS)/acdb/src/*.c) \
	$(wildcard $(GS)/gsl/src/*.c)

all: gslprobe

gslprobe: gslprobe.c stubs.c $(SRC)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ $(LDLIBS)

clean:
	rm -f gslprobe

.PHONY: all clean
