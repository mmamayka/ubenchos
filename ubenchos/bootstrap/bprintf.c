#include <stddef.h>
#include <stdarg.h>
#include "bootstrap.h"

static void reverse(char* str, size_t len) {
    size_t start = 0;
    size_t end = len - 1;

    while(start < end) {
        char tmp = str[start];
        str[start] = str[end];
        str[end] = tmp;

        ++start;
        --end;
    }
}

static char* itoa(int num, char* str, int base) {
    if(num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    size_t i = 0;
    int negative = 0;

    if(base == 10 && num < 0) {
        negative = 1;
        num = -num;
    }

    while(num != 0) {
        int rem = num % base;
        str[i++] = rem >= 10 ? 'a' + rem - 10 : '0' + rem;
        num /= base;
    }

    if(negative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    reverse(str, i);

    return str;
}

void bprintf(char const* format, ...) {
    char buffer[64];

    va_list l;
    va_start(l, format);

    while(*format) {
        if(*format == '%') {
            char command = *(format + 1);
            if(command == '\0') {
                tty_putc('%');
                break;
            } else {
                switch(command) {
                case 'i':
                    tty_puts(itoa(va_arg(l, int), buffer, 10));
                    break;

                case 'x':
                    tty_puts(itoa(va_arg(l, int), buffer, 16));
                    break;

                case 's':
                    tty_puts(va_arg(l, char const*));
                    break;

                default:
                    tty_putc('%');
                    tty_putc(command);
                    break;
                }
                format += 2;
            }
        } else {
            tty_putc(*format++);
        }
    }

    va_end(l);
}
