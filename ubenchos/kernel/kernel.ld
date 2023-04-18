OUTPUT_FORMAT(elf64-x86-64)

ENTRY(kmain)

kernel_vir_base =  0xF0100000;

SECTIONS 
{
    . = kernel_vir_base;
    . = ALIGN(4096);

    kernel_vir_start = .;
    .text BLOCK(4K) : AT(ADDR(.text) - kernel_vir_base) {
        *.o(.text)
    }
    .data BLOCK(4K) : AT(ADDR(.data) - kernel_vir_base) {
        *.o(.data .rodata*)
    }

    kernel_vir_edata = .;
    _edata = .;

    .bss BLOCK(4K) : AT(ADDR(.bss) - kernel_vir_base) {
        *.o(.bss*)
        *(COMMON)
    }
    kernel_vir_end = .;
    _end = .;
}
