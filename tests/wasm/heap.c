#include "stdio.h"
#include "stdlib.h"

int memsize() {
    asm(
        "memory.size 0\n"
        "return\n"
    );

    return 0;
}

int main() {
    for(int i=0; i<50; i++) {
        printf("%p of %p\n", malloc(4096), (void*)(memsize()*64*1024));
    }

    return 0;
}

