#include "multiboot2.h"

.section .multiboot

.global boostrap_start
.global bootstrap_edata
.global bootstrap_end

.global BOOTSTRAP
.global _start
_start:
BOOTSTRAP:
    jmp boot

// multiboot2 header (must be 64-bit aligned)
.align MULTIBOOT_TAG_ALIGN
multiboot2_header_start:
.long MULTIBOOT2_HEADER_MAGIC 
.long MULTIBOOT2_ARCHITECTURE_I386
.long multiboot2_header_end - multiboot2_header_start // size
.long -(MULTIBOOT2_HEADER_MAGIC + MULTIBOOT2_ARCHITECTURE_I386 + \
    (multiboot2_header_end - multiboot2_header_start)) // checksum
#   ifndef __ELF__
.align MULTIBOOT_TAG_ALIGN
multiboot2_address_tag_start:
.short MULTIBOOT_HEADER_TAG_ADDRESS
.short MULTIBOOT_HEADER_TAG_OPTIONAL
.long multiboot2_address_tag_end - multiboot2_address_tag_start
.long multiboot2_header_start // header_addr
.long boostrap_start // load_addr
.long bootstrap_edata // load_end_addr
.long bootstrap_end // bss_end_addr
multiboot2_address_tag_end:
.align MULTIBOOT_TAG_ALIGN
multiboot2_entry_address_tag_start:
.short MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS
.short MULTIBOOT_HEADER_TAG_OPTIONAL
.long multiboot2_entry_address_tag_end - multiboot2_entry_address_tag_start
.long boot // entry_addr
multiboot2_entry_address_tag_end:
#   endif /* __ELF__ */
.align MULTIBOOT_TAG_ALIGN
multiboot2_consone_flags_tag_start:
.short MULTIBOOT_HEADER_TAG_CONSOLE_FLAGS
.short MULTIBOOT_HEADER_TAG_OPTIONAL
.long multiboot2_consone_flags_tag_end - multiboot2_consone_flags_tag_start
.long MULTIBOOT_CONSOLE_FLAGS_EGA_TEXT_SUPPORTED | \
    MULTIBOOT_CONSOLE_FLAGS_CONSOLE_REQUIRED
multiboot2_consone_flags_tag_end:
// .align MULTIBOOT_TAG_ALIGN
// multiboot2_framebuffer_tag_start:
// .short MULTIBOOT_HEADER_TAG_FRAMEBUFFER
// .short MULTIBOOT_HEADER_TAG_OPTIONAL
// .long multiboot2_framebuffer_tag_end - multiboot2_framebuffer_tag_start
// .long 1024 // width
// .long 768 // height
// .long 32 // depth
// multiboot2_framebuffer_tag_end:
.align MULTIBOOT_TAG_ALIGN
.short MULTIBOOT_HEADER_TAG_END
.short 0
.long 0
multiboot2_header_end:

.section .text

.global pre_init
boot:
    mov $.pre_init_stack_top, %esp // make usable stack
    mov $0, %ebp

    push $0 // set flags to good state
    popf

    push $0

    push %ebx // multiboot information struct
    push %eax // multiboot magic number

    call pre_init // enter the high level boostrap code

    cli // disable interrupts to hang in halt loop
.halt_loop:
    hlt
    jmp .halt_loop

// stack
.section .bss
.align 16
.pre_init_stack_bottom:
.skip 4096
.pre_init_stack_top:

