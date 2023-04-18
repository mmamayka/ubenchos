#ifndef UBENCHOS_BOOTSTRAP_H
#define UBENCHOS_BOOTSTRAP_H

#include <stdint.h>
#include <stddef.h>

#define BOOTSTRAP_MAX_MODULES 8

typedef struct module_info_s {
    uint32_t start;
    uint32_t end;
    char const* command_line;
} module_info_t;

typedef struct bootstrap_info_s {
    uint32_t mem_lower;
    uint32_t mem_upper;

    char const* command_line;

    module_info_t modules[BOOTSTRAP_MAX_MODULES];
    uint32_t nmodules;
} bootstrap_info_t;

extern bootstrap_info_t bootstrap_info;

void multiboot_parse_mbi(uint32_t mbi);

void tty_init(void* memory, size_t pitch, size_t width, size_t height,
    size_t bpc);
void tty_putc(char c);
void tty_puts(char const* s);

void bootstrap_do_panic();
int cputest_cpuid_present();
int cputest_paging_present();
int cputest_64mode_present();

void pre_init(uint32_t magic, uint32_t mbi);
void bootstrap_panic(char const* str);

void bprintf(char const* format, ...);

#endif
