#include "unistd.h"


/* ***************************************************************************
* GLOBALS
*/

extern int8_t __heap_base;

static int8_t* _heap_base = &__heap_base;
static int8_t* _heap_brk  = &__heap_base;


/* ***************************************************************************
* PUBLIC FUNCTIONS
*/

int isatty(int fd) {
    /* FIXME */
    return fd < 3 ? 1 : 0;
}

void* sbrk(size_t incr) {
    int8_t* last = _heap_brk;
    size_t memsize = (size_t)__builtin_wasm_memory_size(0) * LIBC_WASM_PAGE_SIZE;

    _heap_brk += LIBC_WASM_ALIGN_CEIL(incr);

    /* Grow memory if needed */
    if((size_t)_heap_brk > memsize) {
        int npages = (((size_t)_heap_brk) - memsize + LIBC_WASM_PAGE_SIZE - 1) / LIBC_WASM_PAGE_SIZE;

        __builtin_wasm_memory_grow(0, npages);
    }

    return last;
}
