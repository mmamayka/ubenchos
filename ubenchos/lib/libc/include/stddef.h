#ifndef UBENCHOS_LIBC_STDDEF_H
#define UBENCHOS_LIBC_STDDEF_H

#ifdef __GNUC__

#if !defined(__PTRDIFF_TYPE__) || !defined(__SIZE_TYPE__)
#error "Used GCC version does not provide neccessary ptrdif_t & size_t macros"
#endif

typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __SIZE_TYPE__ size_t;

#define NULL (void*)0

#define offsetof(type, member) ((size_t)&(((type*)0)->member))

#else
#error "Unsupported compiler"
#endif /* __GNUC__ */

#endif /* UBENCHOS_LIBC_STDDEF_H */
