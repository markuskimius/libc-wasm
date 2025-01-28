#ifndef _LIBC_WASM_H_
#define _LIBC_WASM_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif


#define LIBC_WASM_VERSION_MAJOR 0
#define LIBC_WASM_VERSION_MINOR 20
#define LIBC_WASM_VERSION_PATCH 0
#define LIBC_WASM_PAGE_SIZE     (64*1024)
#define LIBC_WASM_ALIGN_SIZE    __BIGGEST_ALIGNMENT__
#define LIBC_WASM_ALIGN_MASK    (LIBC_WASM_ALIGN_SIZE-1)
#define LIBC_WASM_ALIGN_CEIL(x) (((uintmax_t)(x)+LIBC_WASM_ALIGN_MASK) & ~LIBC_WASM_ALIGN_MASK)

#if   defined(__wasm32) || defined(__wasm32__)
    #define LIBC_WASM 32
#elif defined(__wasm64) || defined(__wasm64__)
    #define LIBC_WASM 64
#else
    #define LIBC_WASM 1
#endif

#define LIBC_WASM_VERSION_LT(major,minor,patch) ( \
    (                                             \
        LIBC_WASM_VERSION_MAJOR < major           \
    )                                             \
    ||                                            \
    (                                             \
        LIBC_WASM_VERSION_MAJOR == major &&       \
        LIBC_WASM_VERSION_MINOR < minor           \
    )                                             \
    ||                                            \
    (                                             \
        LIBC_WASM_VERSION_MAJOR == major &&       \
        LIBC_WASM_VERSION_MINOR == minor &&       \
        LIBC_WASM_VERSION_PATCH < patch           \
    )                                             \
)
#define LIBC_WASM_VERSION_GT(major,minor,patch) ( \
    (                                             \
        LIBC_WASM_VERSION_MAJOR > major           \
    )                                             \
    ||                                            \
    (                                             \
        LIBC_WASM_VERSION_MAJOR == major &&       \
        LIBC_WASM_VERSION_MINOR > minor           \
    )                                             \
    ||                                            \
    (                                             \
        LIBC_WASM_VERSION_MAJOR == major &&       \
        LIBC_WASM_VERSION_MINOR == minor &&       \
        LIBC_WASM_VERSION_PATCH > patch           \
    )                                             \
)
#define LIBC_WASM_VERSION_GE(major,minor,patch) (!LIBC_WASM_VERSION_LT(major,minor,patch))
#define LIBC_WASM_VERSION_LE(major,minor,patch) (!LIBC_WASM_VERSION_GT(major,minor,patch))
#define LIBC_WASM_VERSION_EQ(major,minor,patch) (LIBC_WASM_VERSION_LE(major,minor,patch) && LIBC_WASM_VERSION_GE(major,minor,patch))


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _LIBC_WASM_H_ */
