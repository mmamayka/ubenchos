CPPFLAGS := -DKERNEL -nostdlib -ffreestanding \
	-Iinclude

CFLAGS := -ffreestanding -nostdlib -fno-pie -fno-pic -no-pie \
	-Iinclude -O3 -g

LDFLAGS := -ffreestanding -fno-pie -fno-pic -no-pie -nostdlib -g

ASFLAGS := $(CFLAGS) $(CPPFLAGS)

AS := gcc -x assembler-with-cpp -DASM_FILE -c
CC := gcc
LD := gcc

BINARY_UNSTRIPPED := kernel-unstripped.elf
BINARY := kernel.elf
SYMBOLS := kernel.sym
LINKER := kernel.ld

include ../Makefile.inc
