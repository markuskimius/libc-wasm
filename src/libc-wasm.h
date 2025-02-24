#ifndef _LIBC_WASM_H_
#define _LIBC_WASM_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif


/* ***************************************************************************
* BASE CONSTANTS
*/

#define LIBC_WASM               1
#define LIBC_WASM_WORDSIZE      32

#if defined(__wasm64) || defined(__wasm64__)
#define LIBC_WASM_WORDSIZE      64
#endif


/* ***************************************************************************
* VERSIONING
*/

#define LIBC_WASM_VERSION_MAJOR 0
#define LIBC_WASM_VERSION_MINOR 23
#define LIBC_WASM_VERSION_PATCH 0

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


/* ***************************************************************************
* MACROS
*/

#define LIBC_WASM_PAGE_SIZE     (64*1024)
#define LIBC_WASM_ALIGN_SIZE    __BIGGEST_ALIGNMENT__
#define LIBC_WASM_ALIGN_MASK    (LIBC_WASM_ALIGN_SIZE-1)
#define LIBC_WASM_ALIGN_CEIL(x) (((uintmax_t)(x)+LIBC_WASM_ALIGN_MASK) & ~LIBC_WASM_ALIGN_MASK)
#define LIBC_WASM_POW2_CEIL(x)  (1 << (sizeof(x)*8 - __builtin_clzg(x-1,(int)sizeof(x)*8)))  /* Ceil to the closest power of 2; if x==0 -> 1 */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _LIBC_WASM_H_ */
