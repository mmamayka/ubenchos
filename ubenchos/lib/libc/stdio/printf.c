#include "stddef.h"
#include "stdint.h"
#include "stdarg.h"
#include "ctype.h"
#include "limits.h"

#ifndef UBENCHOS_BOOTSTRAP

extern int bootstrap_puts(char const* str);
extern int bootstrap_putc(char ch);

#define FLAG_NO 0
#define FLAG_LEFT_ALIGN 1
#define FLAG_FORCE_ADD_SIGN 2
#define FLAG_SPACE_IF_NO_SIGN 4
#define FLAG_FORCE_PREFIX_OR_DOT 8
#define FLAG_LEFT_PAD_ZEROES 16
#define FLAG_UPPERCASE 32

#define WIDTH_IN_EXTRA_ARG INT_MIN
#define PRECISION_IN_EXTRA_ARG INT_MIN

#define LENGTH_INT 0
#define LENGTH_UINT LENGTH_INT
#define LENGTH_DOUBLE LENGTH_INT
#define LENGTH_PCHAR LENGTH_INT
#define LENGTH_PVOID LENGTH_INT
#define LENGTH_PINT LENGTH_INT

#define LENGTH_CHAR 1
#define LENGTH_UCHAR LENGTH_CHAR

#define LENGTH_SHORT 2
#define LENGTH_USHORT LENGTH_SHORT
#define LENGTH_PSHORT LENGTH_SHORT

#define LENGTH_LONG 3
#define LENGTH_ULONG LENGTH_LONG
#define LENGTH_PLONG LENGTH_LONG

#define LENGTH_LONGLONG 4
#define LENGTH_ULONGLONG LENGTH_LONGLONG
#define LENGTH_PLONGLONG LENGTH_LONGLONG

#define LENGTH_INTMAX 5
#define LENGTH_UINTMAX LENGTH_INTMAX
#define LENGTH_PINTMAX LENGTH_INTMAX

#define LENGTH_SIZE 6
#define LENGTH_PSIZE LENGTH_SIZE

#define LENGTH_PTRDIFF 7
#define LENGTH_PPTRDIR LENGTH_PTRDIFF

#define LENGTH_LONGDOUBLE 8

static char const* parse_int10_from_string(const char* string, int* pval) {
    int val = 0;
    while(*string >= '0' && *string <= '9') {
        val = val * 10 + (int)(*string - '0');
        ++string;
    }

    *pval = val;
    return string;
}

static char const* parse_flags(char const* format, int* pflags) {
    int flags = FLAG_NO;
    for(;; ++format) {
        switch(*format) {
        case '-':
            flags |= FLAG_LEFT_ALIGN;
            break;
        case '+':
            flags |= FLAG_FORCE_ADD_SIGN;
            break;
        case ' ':
            flags |= FLAG_SPACE_IF_NO_SIGN;
            break;
        case '#':
            flags |= FLAG_FORCE_PREFIX_OR_DOT;
            break;
        case '0':
            flags |= FLAG_LEFT_PAD_ZEROES;
            break;

        default:
            *pflags = flags;
            return format;
        }
    }
}

static char const* parse_width(char const* format, int* pwidth) {
    int width = 0;
    if(*format == '*') {
        width = WIDTH_IN_EXTRA_ARG;
    } else {
        format = parse_int10_from_string(format, &width);
    }

    *pwidth = width;
    return format;
}

static char const* parse_precision(char const* format, int* pprecision) {
    int precision = 0;
    if(*format == '.') {
        ++format;
        if(*format == '*') {
            precision = PRECISION_IN_EXTRA_ARG;
        } else {
            format = parse_int10_from_string(format, &precision);
        }
    }

    *pprecision = precision;
    return format;
}

static char const* parse_length(char const* format, int* plength) {
    int length = LENGTH_INT;
    switch(*format) {
    case 'h':
        ++format;
        switch(*format) {
        case 'h':
            ++format;
            length = LENGTH_CHAR;
            break;
        default:
            length = LENGTH_SHORT;
            break;
        }
        break;

    case 'l':
        ++format;
        switch(*format) {
        case 'l':
            ++format;
            length = LENGTH_LONGLONG;
            break;
        default:
            length = LENGTH_LONG;
            break;
        }
        break;
    case 'j':
        ++format;
        length = LENGTH_INTMAX;
        break;

    case 'z':
        ++format;
        length = LENGTH_SIZE;
        break;
    
    case 't':
        ++format;
        length = LENGTH_PTRDIFF;
        break;

    case 'L':
        ++format;
        length = LENGTH_LONGDOUBLE;
        break;
    }

    *plength = length;
    return format;
}

static void reverse(char* start, char* end) {
    if(start == end) {
        return;
    }

    --end;

    while(start < end) {
        char tmp = *start;
        *start = *end;
        *end = tmp;
    }
}

static int lltoaf(char* buffer, long long value, int flags, 
        int min_char_width, int min_dig_width) {
    char* pos = buffer;

    int negative = value < 0ll;
    if(negative) {
        value = -value;
    }

    while(value) {
        *pos = value % 10 + '0';
        value /= 10;
        ++pos;
    }

    for(; pos < buffer + min_dig_width; ++pos) {
        *pos = '0';
    }

    if(negative) {
        *pos++ = '-';
    } else {
        if(flags & FLAG_FORCE_ADD_SIGN) {
            *pos++ = '+';
        } else if(flags & FLAG_SPACE_IF_NO_SIGN) {
            *pos++ = ' ';
        }
    }

    if(flags & FLAG_LEFT_ALIGN) {
        reverse(buffer, pos);
        for(; pos < buffer + min_char_width; ++pos) {
            *pos = ' ';
        }
    } else {
        char pad = flags & FLAG_LEFT_PAD_ZEROES ? '0' : ' ';
        for(; pos < buffer + min_char_width; ++pos) {
            *pos = pad;
        }
        reverse(buffer, pos);
    }

    *pos++ = '\0';

    return (int)(pos - buffer);
}

static int ulltoaf(char* buffer, unsigned long long value, int flags, 
        int min_char_width, int min_dig_width, int base) {
    char* pos = buffer;

    while(value) {
        *pos = value % base + '0';
        value /= base;
        ++pos;
    }

    for(; pos < buffer + min_dig_width; ++pos) {
        *pos = '0';
    }

    if(flags & FLAG_FORCE_ADD_SIGN) {
        *pos++ = '+';
    } else if(flags & FLAG_SPACE_IF_NO_SIGN) {
        *pos++ = ' ';
    }

    if(flags & FLAG_FORCE_PREFIX_OR_DOT) {
        if(base == 16) {
            *pos++ = 'x';
            *pos++ = '0';
        } else {
            *pos++ = '0';
        }
    }

    if(flags & FLAG_LEFT_ALIGN) {
        reverse(buffer, pos);
        for(; pos < buffer + min_char_width; ++pos) {
            *pos = ' ';
        }
    } else {
        char pad = flags & FLAG_LEFT_PAD_ZEROES ? '0' : ' ';
        for(; pos < buffer + min_char_width; ++pos) {
            *pos = pad;
        }
        reverse(buffer, pos);
    }

    if(flags & FLAG_UPPERCASE) {
        for(char* c = buffer; c < pos; ++c) {
            *c = toupper(*c);
        }
    }

    *pos++ = '\0';

    return (int)(pos - buffer);

}

static int print_signed(va_list arg, int flags, int width, 
        int precision, int length) {
    long long value;
    switch(length) {
    case LENGTH_INT:
        value = (int)va_arg(arg, int);
        break;
    case LENGTH_CHAR:
        value = (char)va_arg(arg, int);
        break;
    case LENGTH_SHORT:
        value = (short)va_arg(arg, int);

    case LENGTH_LONG:
        value = (long)va_arg(arg, long);
        break;
    case LENGTH_LONGLONG:
        value = (long long)va_arg(arg, long long);
        break;
    case LENGTH_INTMAX:
        value = (intmax_t)va_arg(arg, intmax_t);
        break;
    case LENGTH_PTRDIFF:
        value = (ptrdiff_t)va_arg(arg, ptrdiff_t);
        break;
    }

    char buffer[32];
    lltoaf(buffer, value, flags, width, precision);
    return bootstrap_puts(buffer);
}

static int print_unsigned(va_list arg, int flags, int width, 
        int precision, int length, int base) {
    unsigned long long value;
    switch(length) {
    case LENGTH_UINT:
        value = (unsigned int)va_arg(arg, unsigned int);
        break;
    case LENGTH_UCHAR:
        value = (unsigned char)va_arg(arg, unsigned int);
        break;
    case LENGTH_USHORT:
        value = (unsigned short)va_arg(arg, unsigned int);

    case LENGTH_ULONG:
        value = (unsigned long)va_arg(arg, unsigned long);
        break;
    case LENGTH_ULONGLONG:
        value = (unsigned long long)va_arg(arg, unsigned long long);
        break;
    case LENGTH_UINTMAX:
        value = (uintmax_t)va_arg(arg, uintmax_t);
        break;
    case LENGTH_SIZE:
        value = (size_t)va_arg(arg, size_t);
        break;
    }

    char buffer[32];
    ulltoaf(buffer, value, flags, width, precision, base);
    return bootstrap_puts(buffer);
}

int vprintf(char const* format, va_list arg) {
    int arg_flags = FLAG_NO;
    int arg_width = 0;
    int arg_precision = 0;
    int arg_length = 0;
    int printed = 0;

    if(!*format) {
        return 0;
    }
    do {
        if(*format == '%') {
            ++format;

            format = parse_flags(format, &arg_flags);
            format = parse_width(format, &arg_width);
            if(arg_width == WIDTH_IN_EXTRA_ARG) {
                arg_width = va_arg(arg, int);
            }

            format = parse_precision(format, &arg_precision);
            if(arg_precision == PRECISION_IN_EXTRA_ARG) {
                arg_precision = va_arg(arg, int);
            }

            format = parse_length(format, &arg_length);

            switch(*format) {
            case '%':
                ++format;
                printed += bootstrap_putc('%');
                break;

            case 'c':
                ++format;
                printed += bootstrap_putc((char)va_arg(arg, int));
                break;

            case 's':
                ++format;
                printed += bootstrap_puts(va_arg(arg, char const*));
                break;

            case 'i':
            case 'd':
                ++format;
                printed += print_signed(arg, arg_flags, arg_width, 
                        arg_precision, arg_length);
                break;

            case 'u':
                ++format;
                printed += print_unsigned(arg, arg_flags, arg_width, 
                        arg_precision, arg_length, 10);
                break;
            case 'o':
                ++format;
                print_unsigned(arg, arg_flags, arg_width, arg_precision,
                        arg_length, 8);
                break;
            case 'p':
            case 'x':
                ++format;
                printed += print_unsigned(arg, arg_flags, arg_width, 
                        arg_precision, arg_length, 16);
                break;
            case 'X':
                ++format;
                arg_flags |= FLAG_UPPERCASE;
                printed += print_unsigned(arg, arg_flags, arg_width, 
                        arg_precision, arg_length, 16);
                break;
            case 'n':
                ++format;
                *(va_arg(arg, signed int*)) = printed;
                break;
            }
        } else {
            printed += bootstrap_putc(*format);
        }
    } while(*format);
    return printed;
}

int printf(char const* format, ...) {
    va_list list;
    va_start(list, format);
    int res = vprintf(format, list);
    va_end(list);

    return res;
}
#else /* UBENCHOS_BOOTSTRAP */
#   error "Only bootstrap version of printf/vprintf is supported now"
#endif /* UBENCHOS_BOOTSTRAP */
