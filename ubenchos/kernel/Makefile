include ../../make/ubenchos-common-config.mk
include ../../make/ubenchos-kernel-config.mk

CPPFLAGS := -DKERNEL -nostdlib -ffreestanding -Iinclude

CFLAGS := -ffreestanding -nostdlib -fno-pie -fno-pic -no-pie \
	-Iinclude -O3 -g

LDFLAGS := -ffreestanding -fno-pie -fno-pic -no-pie -nostdlib -g

ASFLAGS := $(CFLAGS) $(CPPFLAGS)

AS := gcc -x assembler-with-cpp -DASM_FILE -c
CC := gcc
LD := gcc

NEED_STRIPPING := 1
EXECUTABLE_UNSTRIPPED := kernel-unstripped.elf
EXECUTABLE_SYMBOLS := kernel.sym
EXECUTABLE := kernel.elf
LINKER_SCRIPT := kernel.ld

include ../../make/build-executable.mk
