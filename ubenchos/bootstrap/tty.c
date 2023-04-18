#include <stddef.h>
#include <stdint.h>

#define TAB_W 4

static void* tty_memory;
static size_t tty_pitch;
static size_t tty_width;
static size_t tty_height;
static size_t tty_bpc;

static size_t tty_xpos;
static size_t tty_ypos;

static void tty_clear() {
    tty_xpos = tty_ypos = 0;

    for(size_t i = 0; i < tty_pitch * tty_height; ++i) {
        *((char*)tty_memory + i) = 0;
    }
}

static void tty_scroll() {
    ++tty_ypos;

    if(tty_ypos == tty_height) {
        for(size_t y = 1; y < tty_height; ++y) {
            for(size_t x = 0; x < tty_width; ++x) {
                *((char*)tty_memory + (y - 1) * tty_pitch + x * tty_bpc) =
                    *((char*)tty_memory + y * tty_pitch + x * tty_bpc);
            }
        }
        for(size_t x = 0; x < tty_width; ++x) {
            *((char*)tty_memory + (tty_height - 1) * 
                tty_pitch + x * tty_bpc) = 0;
        }
        --tty_ypos;
    }
}

static void tty_retcar() {
    tty_xpos = 0;
}

void tty_init(void* memory, size_t pitch, size_t width, size_t height,
        size_t bpc) {
    tty_memory = memory;
    tty_pitch = pitch;
    tty_width = width;
    tty_height = height;
    tty_bpc = bpc;

    tty_clear();
}

static void tty_putc_raw(char c) {
    size_t offset =  tty_xpos * tty_bpc + tty_ypos * tty_pitch;
    uint16_t* entry_pos = (uint16_t*)((char*)tty_memory + offset);

    *entry_pos = (uint16_t)c | 0x0F00;

    ++tty_xpos;
    if(tty_xpos == tty_width) {
        tty_xpos = 0;
        tty_scroll();
    }
}

void tty_putc(char c) {
    switch(c) {
    case '\n':
        tty_retcar();
        tty_scroll();
        break;

    case '\t':
        for(size_t i = 0; i < TAB_W; ++i) {
            tty_putc_raw(' ');
        }
        break;

    case '\r':
        tty_retcar();
        break;

    default:
        tty_putc_raw(c);
        break;
    }
}

void tty_puts(char const* s) {
    while(*s) {
        tty_putc(*s);
        ++s;
    }
}
