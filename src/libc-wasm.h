#ifndef _LIBC_WASM_H_
#define _LIBC_WASM_H_

#ifdef __cplusplus
extern "C" {
#endif


#define LIBC_WASM_VERSION_MAJOR 0
#define LIBC_WASM_VERSION_MINOR 9
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


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _LIBC_WASM_H_ */
