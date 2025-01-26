#include "stdio.h"

int main() {
    printf("LIBC_WASM               : %d\n", LIBC_WASM);
    printf("LIBC_WASM_PAGE_SIZE     : %d\n", LIBC_WASM_PAGE_SIZE);
    printf("LIBC_WASM_ALIGN_SIZE    : %d\n", LIBC_WASM_ALIGN_SIZE);
    printf("LIBC_WASM_ALIGN_MASK    : %d\n", LIBC_WASM_ALIGN_MASK);
    printf("LIBC_WASM_VERSION_MAJOR : %d\n", LIBC_WASM_VERSION_MAJOR);
    printf("LIBC_WASM_VERSION_MINOR : %d\n", LIBC_WASM_VERSION_MINOR);
    printf("LIBC_WASM_VERSION_PATCH : %d\n", LIBC_WASM_VERSION_PATCH);

    for(int i=0; i<100; i++) {
        printf("%2d => %d\n", i, (int)LIBC_WASM_ALIGN_CEIL(i));
    }

    return 0;
}
