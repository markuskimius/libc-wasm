#include "string.h"
#include "stdlib.h"

void* memcpy(void* dest, const void* src, size_t n) {
    int8_t* dp = dest;
    const int8_t* sp = src;

    for(size_t i=0; i<n; i++) {
        *dp++ = *sp++;
    }

    return dest;
}

void* memset(void* s, int c, size_t n) {
    int8_t* cp = s;

    for(size_t i=0; i<n; i++) {
        *cp++ = c;
    }

    return s;
}

size_t strlen(const char* s) {
    size_t i = 0;

    while(*s) {
        s++;
        i++;
    }

    return i;
}
