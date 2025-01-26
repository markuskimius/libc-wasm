#include "stdio.h"

int main() {
    printf("LIBC_WASM               : %d\n", LIBC_WASM);
    printf("LIBC_WASM_NALIGN        : %d\n", LIBC_WASM_NALIGN);
    printf("LIBC_WASM_VERSION_MAJOR : %d\n", LIBC_WASM_VERSION_MAJOR);
    printf("LIBC_WASM_VERSION_MINOR : %d\n", LIBC_WASM_VERSION_MINOR);
    printf("LIBC_WASM_VERSION_PATCH : %d\n", LIBC_WASM_VERSION_PATCH);

    return 0;
}
