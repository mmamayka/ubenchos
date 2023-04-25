OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)

ENTRY(BOOTSTRAP)

bootstrap_load_address = 0x00100000;

SECTIONS {
    . = bootstrap_load_address;
    . = ALIGN(4096);

    _bootstrap_start = .;

    .text BLOCK(4K) : ALIGN(4K) {
        *.o(.multiboot .text)
    }
    .data BLOCK(4K) : ALIGN(4K) {
        *.o(.data .rodata*)
    }

    _bootstrap_edata = .; _edata = .;

    .bss BLOCK(4K) : ALIGN(4K) {
        *.o(.bss*)
        *(COMMON)
    }
    _bootstrap_end = .; _end = .;
}
