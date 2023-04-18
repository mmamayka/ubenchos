OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)

ENTRY(BOOTSTRAP)

SECTIONS {
    . = ALIGN(4096);

    bootstrap_start = .;
    .text BLOCK(4K) : ALIGN(4K) {
        *.o(.multiboot .text)
    }
    .data BLOCK(4K) : ALIGN(4K) {
        *.o(.data .rodata*)
    }
    boostrap_edata = .;
    _edata = .;

    .bss BLOCK(4K) : ALIGN(4K) {
        *.o(.bss*)
        *(COMMON)
    }
    boostrap_end = .;
    _end = .;
}
