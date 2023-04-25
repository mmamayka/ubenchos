#include <string.h>

void* memcpy(void* dest, void const* src, size_t size) {
    for(size_t i = 0; i < size; ++i) {
        *(char*)(dest + i) = *(char const*)(src + i);
    }
    return dest;
}

void* memmove(void* dest, void const* src, size_t size) {
    return memcpy(dest, src, size);
}

void* memset(void* dest, int val, size_t size) {
    for(size_t i = 0; i < size; ++i) {
        *(char*)(dest + i) = (char)val;
    }
    return dest;
}

int memcmp(void const* src1, void const* src2, size_t size) {
    for(size_t i = 0; i < size; ++i) {
        char diff = *(char const*)(src1 + i) - *(char const*)(src2 + i);
        if(diff != 0) {
            return diff < 0 ? -1 : 1;
        }
    }
    return 0;
}

size_t strlen(char const* str) {
    size_t len = 0;
    while(*str++) {
        ++len;
    }
    return len;
}

int strcmp(char const* src1, char const* src2) {
    while(*src1) {
        char diff = *src1 - *src2;
        if(diff == 0)
            continue;

        return diff < 0 ? -1 : 1;
    }
    return *src2 == 0;
}
