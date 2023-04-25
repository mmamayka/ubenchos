#include "multiboot2.h"
#include "bootstrap.h"

static struct multiboot_tag const* multiboot_first_tag(
        struct multiboot_tag const* ptags) {
    uint8_t const* ptr = (uint8_t const*)ptags;

    struct multiboot_tag const* first_tag =
        (struct multiboot_tag const*)(ptr + sizeof(uint32_t) * 2);

    return first_tag;
}
static struct multiboot_tag const* multiboot_next_tag(
        struct multiboot_tag const* cur_tag) {
    if(cur_tag->type == MULTIBOOT_TAG_TYPE_END) {
        return NULL;
    }

    size_t aligned8_offset = (cur_tag->size + (MULTIBOOT_TAG_ALIGN - 1)) &
        ~(MULTIBOOT_TAG_ALIGN - 1);

    uint8_t const* ptr = (uint8_t const*)cur_tag;

    struct multiboot_tag const* next_tag =
        (struct multiboot_tag const*)(ptr + aligned8_offset);

    return next_tag;
}

static void multiboot_parse_framebuffer_tag(struct multiboot_tag const* tag) {
    struct multiboot_tag_framebuffer const* fbtag = 
        (struct multiboot_tag_framebuffer const*)tag;

    if(fbtag->common.framebuffer_type == MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT) {
        tty_init((void*)fbtag->common.framebuffer_addr,
            fbtag->common.framebuffer_pitch,
            fbtag->common.framebuffer_width,
            fbtag->common.framebuffer_height,
            fbtag->common.framebuffer_bpp / 8);
    }
}

static void multiboot_parse_meminfo(struct multiboot_tag const* tag) {
    struct multiboot_tag_basic_meminfo const* mtag = 
        (struct multiboot_tag_basic_meminfo*)tag;

    bootstrap_info.mem_lower = mtag->mem_lower;
    bootstrap_info.mem_upper = mtag->mem_upper;
}

static void multiboot_parse_cmdline(struct multiboot_tag const* tag) {
    struct multiboot_tag_string* stag = (struct multiboot_tag_string*)tag;
    bootstrap_info.command_line = stag->string;
}

void multiboot_parse_module(struct multiboot_tag const* tag) {
    struct multiboot_tag_module const* mtag = 
        (struct multiboot_tag_module const*)tag;
    bootstrap_info.modules[bootstrap_info.nmodules].start = mtag->mod_start;
    bootstrap_info.modules[bootstrap_info.nmodules].end = mtag->mod_end;
    bootstrap_info.modules[bootstrap_info.nmodules].command_line = 
        mtag->cmdline;
    ++bootstrap_info.nmodules;
}

void multiboot_parse_mbi(uint32_t mbi) {
    bootstrap_info.command_line = NULL;
    bootstrap_info.mem_lower = bootstrap_info.mem_upper = 0;
    bootstrap_info.nmodules = 0;

    uint64_t qw_mbi = (uint64_t)mbi;
    struct multiboot_tag const* ptags = (struct multiboot_tag const*)qw_mbi;

    for(struct multiboot_tag const* ptag = multiboot_first_tag(ptags);
            ptag != NULL; ptag = multiboot_next_tag(ptag)) {
        switch(ptag->type) {
        case MULTIBOOT_TAG_TYPE_FRAMEBUFFER:
            multiboot_parse_framebuffer_tag(ptag);
            break;
        case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
            multiboot_parse_meminfo(ptag);
            break;
        case MULTIBOOT_TAG_TYPE_CMDLINE:
            multiboot_parse_cmdline(ptag);
            break;
        case MULTIBOOT_TAG_TYPE_MODULE:
            multiboot_parse_module(ptag);
            break;
        }
    }
}

