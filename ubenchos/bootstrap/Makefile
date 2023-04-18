CPPFLAGS := -DBOOSTSTRAP -nostdlib -ffreestanding \
	-I../kernel/include \
	-I../../third_party/grub/include

CFLAGS := -ffreestanding -nostdlib -m32 -fno-pic -fno-pie -no-pie -O3 -g

LDFLAGS := -ffreestanding -nostdlib -m32 -fno-pic -fno-pie -no-pie -g

ASFLAGS := $(CFLAGS) $(CPPFLAGS)

AS := gcc -x assembler-with-cpp -DASM_FILE -c
CC := gcc
LD := gcc

BINARY_UNSTRIPPED := bootstrap-unstripped.elf
BINARY := bootstrap.elf
SYMBOLS := bootstrap.sym
LINKER := bootstrap.ld

include ../Makefile.inc

