#ifndef UBENCHOS_LIBC_STDINT_H
#define UBENCHOS_LIBC_STDINT_H

#ifdef __GNUC__
#if !defined(__INTMAX_TYPE__) || !defined(__UINTMAX_TYPE__) || \
   !defined(__INT8_TYPE__) || !defined(__INT16_TYPE__) || \
   !defined(__INT32_TYPE__) || !defined(__INT64_TYPE__) || \
   !defined(__UINT8_TYPE__) || !defined(__UINT16_TYPE__) || \
   !defined(__UINT32_TYPE__) || !defined(__UINT64_TYPE__) || \
   !defined(__INT_FAST8_TYPE__) || !defined(__INT_FAST16_TYPE__) || \
   !defined(__INT_FAST32_TYPE__) || !defined(__INT_FAST64_TYPE__) || \
   !defined(__UINT_FAST8_TYPE__) || !defined(__UINT_FAST16_TYPE__) || \
   !defined(__UINT_FAST32_TYPE__) || !defined(__UINT_FAST64_TYPE__) || \
   !defined(__INT_LEAST8_TYPE__) || !defined(__INT_LEAST16_TYPE__) || \
   !defined(__INT_LEAST32_TYPE__) || !defined(__INT_LEAST64_TYPE__) || \
   !defined(__UINT_LEAST8_TYPE__) || !defined(__UINT_LEAST16_TYPE__) || \
   !defined(__UINT_LEAST32_TYPE__) || !defined(__UINT_LEAST64_TYPE__) || \
   !defined(__INTPTR_TYPE__) || !defined(__UINTPTR_TYPE__)
#error "Used GCC version does not provide all neccessary int macros"
#endif

typedef __INTMAX_TYPE__ intmax_t;
typedef __UINTMAX_TYPE__ uintmax_t;

typedef __INT8_TYPE__ int8_t;
typedef __INT16_TYPE__ int16_t;
typedef __INT32_TYPE__ int32_t;
typedef __INT64_TYPE__ int64_t;

typedef __UINT8_TYPE__ uint8_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __UINT32_TYPE__ uint32_t;
typedef __UINT64_TYPE__ uint64_t;

typedef __INT_FAST8_TYPE__ int_fast8_t;
typedef __INT_FAST16_TYPE__ int_fast16_t;
typedef __INT_FAST32_TYPE__ int_fast32_t;
typedef __INT_FAST64_TYPE__ int_fast64_t;

typedef __UINT_FAST8_TYPE__ uint_fast8_t;
typedef __UINT_FAST16_TYPE__ uint_fast16_t;
typedef __UINT_FAST32_TYPE__ uint_fast32_t;
typedef __UINT_FAST64_TYPE__ uint_fast64_t;

typedef __INT_LEAST8_TYPE__ int_least8_t;
typedef __INT_LEAST16_TYPE__ int_least16_t;
typedef __INT_LEAST32_TYPE__ int_least32_t;
typedef __INT_LEAST64_TYPE__ int_least64_t;

typedef __UINT_LEAST8_TYPE__ uint_least8_t;
typedef __UINT_LEAST16_TYPE__ uint_least16_t;
typedef __UINT_LEAST32_TYPE__ uint_least32_t;
typedef __UINT_LEAST64_TYPE__ uint_least64_t;

typedef __INTPTR_TYPE__ intptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;

#if !defined(__INTMAX_MAX__) || !defined(__UINTMAX_MAX__) || \
   !defined(__INT8_MAX__) || !defined(__INT16_MAX__) || \
   !defined(__INT32_MAX__) || !defined(__INT64_MAX__) || \
   !defined(__UINT8_MAX__) || !defined(__UINT16_MAX__) || \
   !defined(__UINT32_MAX__) || !defined(__UINT64_MAX__) || \
   !defined(__INT_FAST8_MAX__) || !defined(__INT_FAST16_MAX__) || \
   !defined(__INT_FAST32_MAX__) || !defined(__INT_FAST64_MAX__) || \
   !defined(__UINT_FAST8_MAX__) || !defined(__UINT_FAST16_MAX__) || \
   !defined(__UINT_FAST32_MAX__) || !defined(__UINT_FAST64_MAX__) || \
   !defined(__INT_LEAST8_MAX__) || !defined(__INT_LEAST16_MAX__) || \
   !defined(__INT_LEAST32_MAX__) || !defined(__INT_LEAST64_MAX__) || \
   !defined(__UINT_LEAST8_MAX__) || !defined(__UINT_LEAST16_MAX__) || \
   !defined(__UINT_LEAST32_MAX__) || !defined(__UINT_LEAST64_MAX__) || \
   !defined(__INTPTR_MAX__) || !defined(__UINTPTR_MAX__)
#error "Used GCC version does not provide all neccessary int macros"
#endif

#define INTMAX_MAX __INTMAX_MAX__
#define UINTMAX_MAX __UINTMAX_MAX__

#define INT8_MAX __INT8_MAX__
#define INT16_MAX __INT16_MAX__
#define INT32_MAX __INT32_MAX__
#define INT64_MAX __INT64_MAX__

#define UINT8_MAX __UINT8_MAX__
#define UINT16_MAX __UINT16_MAX__
#define UINT32_MAX __UINT32_MAX__
#define UINT64_MAX __UINT64_MAX__

#define INT_FAST8_MAX __INT_FAST8_MAX__
#define INT_FAST16_MAX __INT_FAST16_MAX__
#define INT_FAST32_MAX __INT_FAST32_MAX__
#define INT_FAST64_MAX __INT_FAST64_MAX__

#define UINT_FAST8_MAX __UINT_FAST8_MAX__
#define UINT_FAST16_MAX __UINT_FAST16_MAX__
#define UINT_FAST32_MAX __UINT_FAST32_MAX__
#define UINT_FAST64_MAX __UINT_FAST64_MAX__

#define INT_LEAST8_MAX __INT_LEAST8_MAX__
#define INT_LEAST16_MAX __INT_LEAST16_MAX__
#define INT_LEAST32_MAX __INT_LEAST32_MAX__
#define INT_LEAST64_MAX __INT_LEAST64_MAX__

#define UINT_LEAST8_MAX __UINT_LEAST8_MAX__
#define UINT_LEAST16_MAX __UINT_LEAST16_MAX__
#define UINT_LEAST32_MAX __UINT_LEAST32_MAX__
#define UINT_LEAST64_MAX __UINT_LEAST64_MAX__

#define INTPTR_MAX __INTPTR_MAX__
#define UINTPTR_MAX __UINTPTR_MAX__


#define INTMAX_MIN (-INTMAX_MAX - 1)

#define INT8_MIN (-INT8_MAX - 1)
#define INT16_MIN (-INT16_MAX - 1)
#define INT32_MIN (-INT32_MAX - 1)
#define INT64_MIN (-INT64_MAX - 1)

#define INT_FAST8_MIN (-INT_FAST8_MAX - 1)
#define INT_FAST16_MIN (-INT_FAST16_MAX - 1)
#define INT_FAST32_MIN (-INT_FAST32_MAX - 1)
#define INT_FAST64_MIN (-INT_FAST64_MAX - 1)

#define INT_LEAST8_MIN (-INT_LEAST8_MAX - 1)
#define INT_LEAST16_MIN (-INT_LEAST16_MAX - 1)
#define INT_LEAST32_MIN (-INT_LEAST32_MAX - 1)
#define INT_LEAST64_MIN (-INT_LEAST64_MAX - 1)

#define INTPTR_MIN (-INTPTR_MAX - 1)

#if !defined(__INT8_C) || !defined(__INT16_C) ||  \
    !defined(__INT32_C) || !defined(__INT64_C) || \
    !defined(__UINT8_C) || !defined(__UINT16_C) ||  \
    !defined(__UINT32_C) || !defined(__UINT64_C) || \
    !defined(__INTMAX_C) || !defined(__UINTMAX_C)
#error "Used GCC version does not provide all neccessary int macros"
#endif

#define INT8_C(v) __INT8_C(v)
#define INT16_C(v) __INT16_C(v)
#define INT32_C(v) __INT32_C(v)
#define INT64_C(v) __INT64_C(v)

#define UINT8_C(v) __UINT8_C(v)
#define UINT16_C(v) __UINT16_C(v)
#define UINT32_C(v) __UINT32_C(v)
#define UINT64_C(v) __UINT64_C(v)

#define INTMAX_C(v) __INTMAX_C(v)
#define UINTMAX_C(v) __UINTMAX_C(v)

#else /* __GNUC__ */
#error "Unsupported compiler"
#endif /* __GNUC__ */

#endif /* UBENCHOS_LIBC_STDINT_H */
