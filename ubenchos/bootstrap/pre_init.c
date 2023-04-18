#include <stddef.h>
#include <stdint.h>

#include "bootstrap.h"

bootstrap_info_t bootstrap_info = {};

void bootstrap_panic(char const* str) {
    tty_puts("[bootstrap] panic: ");
    tty_puts(str);
    bootstrap_do_panic();
}

static void dump_info() {
    bprintf("[bootstrap] stratup info:\n");

    bprintf("\tmem_lower = 0x%x, mem_upper = 0x%x\n", 
        bootstrap_info.mem_lower, bootstrap_info.mem_upper);

    bprintf("\tcommand_line = \'%s\'\n", bootstrap_info.command_line);
    
    bprintf("\tmodules:\n");
    for(uint32_t i = 0; i < bootstrap_info.nmodules; ++i) {
        bprintf("\t\tstart = %x, end = %x\n", bootstrap_info.modules[i].start,
            bootstrap_info.modules[i].end);
        bprintf("\t\tcommand_line = %s\n\n", 
            bootstrap_info.modules[i].command_line);
    }
}

void pre_init(uint32_t magic, uint32_t mbi) {
    multiboot_parse_mbi(mbi);
    bprintf("[bootstrap] preparing to jump in long mode...\n");

    dump_info();

    if(!cputest_cpuid_present()) {
        bootstrap_panic("\tcpuid not present - quiting\n");
    }
    if(!cputest_64mode_present()) {
        bootstrap_panic("\t64-bit mode not present - quiting\n");
    }
}
