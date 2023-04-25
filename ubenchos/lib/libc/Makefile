include ../../../make/ubenchos-common-config.mk
include $(UBENCHOS_MAKE_DIR)/ubenchos-kernel-config.mk

CPPFLAGS := -DBOOSTSTRAP -nostdinc -ffreestanding -Iinclude

CFLAGS := -ffreestanding -nostdlib -m32 -fno-pic -fno-pie -no-pie -O3 -g \
	-fomit-frame-pointer -fno-exceptions -fno-asynchronous-unwind-tables \
	-fno-unwind-tables -Wall -Wextra

LDFLAGS := -ffreestanding -nostdlib -m32 -fno-pic -fno-pie -no-pie -g

ASFLAGS := $(CFLAGS) $(CPPFLAGS)

LIBRARY := libc.a

SOURCE_DIRS := string stdio ctype

include $(UBENCHOS_MAKE_DIR)/build-library.mk

