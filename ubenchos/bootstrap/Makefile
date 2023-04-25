include ../../make/ubenchos-common-config.mk
include $(UBENCHOS_MAKE_DIR)/ubenchos-kernel-config.mk

CPPFLAGS := -DBOOSTSTRAP -nostdinc -ffreestanding \
	-I../include \

CFLAGS := -ffreestanding -nostdlib -m32 -fno-pic -fno-pie -no-pie -O3 -g \
	-fomit-frame-pointer -fno-exceptions -fno-asynchronous-unwind-tables \
	-fno-unwind-tables -Wall -Wextra

LDFLAGS := -ffreestanding -nostdlib -m32 -fno-pic -fno-pie -no-pie -g

ASFLAGS := $(CFLAGS) $(CPPFLAGS)

NEED_STRIPPING := 1
EXECUTABLE_UNSTRIPPED := bootstrap-unstripped.elf
EXECUTABLE_SYMBOLS := bootstrap.sym
EXECUTABLE := bootstrap.elf
LINKER_SCRIPT := bootstrap.ld

DEPSPATH := $(UBENCHOS_KERNEL_LIB_DIR) $(UBENCHOS_KERNEL_DIR) \
	$(UBENCHOS_THIRD_PARTY_DIR)
DEPS := kernel grub libc

include $(UBENCHOS_MAKE_DIR)/build-executable.mk

