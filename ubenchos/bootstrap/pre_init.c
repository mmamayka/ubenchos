#include <stddef.h>
#include <stdint.h>
#include "sys/elf64.h"

#include "bootstrap.h"

bootstrap_info_t bootstrap_info = {};

void bootstrap_panic(char const* str) {
    tty_puts("[bootstrap] panic: ");
    tty_puts(str);
    bootstrap_do_panic();
}

extern paddr_t _bootstrap_start;
extern paddr_t _bootstrap_edata;
extern paddr_t _bootstrap_end;

static void dump_info() {
    bprintf("[bootstrap] stratup info:\n");

    bprintf("\tbootstrap:\n");
    bprintf("\t\tstart = 0x%x, edata = 0x%x, end = 0x%x\n",
        &_bootstrap_start, &_bootstrap_edata, &_bootstrap_end);
    bprintf("\t\tcommand_line = \'%s\'\n", bootstrap_info.command_line);

    bprintf("\tmem_lower = 0x%x, mem_upper = 0x%x\n", 
        bootstrap_info.mem_lower, bootstrap_info.mem_upper);

    
    bprintf("\tmodules:\n");
    for(size_t i = 0; i < bootstrap_info.nmodules; ++i) {
        bprintf("\t\tstart = %x, end = %x\n", bootstrap_info.modules[i].start,
            bootstrap_info.modules[i].end);
        bprintf("\t\tcommand_line = \'%s\'\n\n", 
            bootstrap_info.modules[i].command_line);
    }
}

int strcmp(char const* str1, char const* str2) {
    while(*str1 != '\0') {
        if(*str1 < *str2) {
            return -1;
        }
        if(*str1 > *str2) {
            return 1;
        }

        ++str1;
        ++str2;
    }
    if(*str2 != '\0') {
        return -1;
    }
    return 0;
}

static module_info_t const* find_module(char const* name) {
    for(module_info_t const* minfo = bootstrap_info.modules; 
            minfo < bootstrap_info.modules + bootstrap_info.nmodules; ++minfo) {
        if(strcmp(minfo->command_line, name) == 0) {
            return minfo;
        }
    }
    return NULL;
}

static int parse_module(module_info_t const* module, uint64_t* paddr,
        uint64_t* vaddr, uint64_t* size, uint64_t* align, uint64_t* pentry) {
    Elf64_Ehdr const* header = (Elf64_Ehdr const*)module->start;
    if(!IS_ELF(*header)) {
        return 0;
    }

    Elf64_Phdr const* pheaders = (Elf64_Phdr const*)(module->start + header->e_phoff);
    size_t npheaders = header->e_phnum;
    size_t spheader = header->e_phentsize;

    for(size_t i = 0; i < npheaders; ++i) {
        Elf64_Phdr const* pheader = pheaders + spheader * i;
        if(pheader->p_type == PT_LOAD) {
            *paddr = (uint64_t*)(module->start + pheader->p_offset);
            *vaddr = pheader->p_vaddr;
            *size = pheader->p_memsz;
            *align = pheader->p_align;
            *pentry = header->e_entry;
            return 1;
        }
    }

    return 0;
}


#ifndef NDEBUG
#   define DUMP_STARTUP_INFO() dump_info()
#else
#   define DUMP_STARTUP_INFO()
#endif

void pre_init(uint32_t magic, paddr_t mbi) {
    multiboot_parse_mbi(mbi);

    DUMP_STARTUP_INFO();

    bprintf("[bootstrap] multiboot info sucessfully parsed, "
        "looking for kernel module...\n");

    module_info_t const* kernel_module = find_module("kernel");
    if(kernel_module == NULL) {
        bootstrap_panic("kernel module not found");
    }

    bprintf(
        "[bootstrap] kernel module was loaded at 0x%x, end address is 0x%x\n",
        kernel_module->start, kernel_module->end);

    bprintf("[bootstrap] parsing kernel elf...\n");

    uint64_t kernel_paddr = 0;
    uint64_t kernel_vaddr = 0;
    uint64_t kernel_size = 0;
    uint64_t kernel_align = 0;
    uint64_t kernel_entry = 0;
    if(!parse_module(kernel_module, &kernel_paddr, &kernel_vaddr, &kernel_size,
            &kernel_align, &kernel_entry)) {
        bootstrap_panic("kernel load section not found");
    }

    bprintf("[bootstrap] kernel elf parsed:\n\tpaddr = %x\n\tvaddr_low = %x\n\t"
        "vaddr_high = %x\n\tsize = %i\n\talign = %i\n\t"
        "entry_low = %x\n\tentry_high = %x", 
        (uint32_t)kernel_paddr, (uint32_t)kernel_vaddr, (uint32_t)(kernel_vaddr >> 32),
        (uint32_t)kernel_size, (uint32_t)kernel_align, 
        (uint32_t)kernel_entry, (uint32_t)(kernel_entry >> 32));
}
