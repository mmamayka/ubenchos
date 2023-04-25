#ifndef UBENCHOS_LIBC_STRING_H
#define UBENCHOS_LIBC_STRING_H

#include <stddef.h>

void* memcpy(void* dest, void const* src, size_t size);
void* memmove(void* dest, void const* src, size_t size);
void* memset(void* dest, int val, size_t size);
int memcmp(void const* src1, void const* src2, size_t size);

size_t strlen(char const* str);
int strcmp(char const* src1, char const* src2);

#endif
