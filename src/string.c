#include "string.h"
#include "ctype.h"
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

int strcmp(const char* s1, const char* s2) {
    int cmp = 0;

    while(cmp==0 && (*s1 || *s2)) {
        cmp = *s1 - *s2;
        s1++;
        s2++;
    }

    return cmp;
}

int strncmp(const char* s1, const char* s2, size_t n) {
    int cmp = 0;

    while(cmp==0 && n && (*s1 || *s2)) {
        cmp = *s1 - *s2;
        s1++;
        s2++;
        n--;
    }

    return cmp;
}

int strcasecmp(const char* s1, const char* s2) {
    int cmp = 0;

    while(cmp==0 && (*s1 || *s2)) {
        cmp = tolower(*s1) - tolower(*s2);
        s1++;
        s2++;
    }

    return cmp;
}

int strncasecmp(const char* s1, const char* s2, size_t n) {
    int cmp = 0;

    while(cmp==0 && n && (*s1 || *s2)) {
        cmp = tolower(*s1) - tolower(*s2);
        s1++;
        s2++;
        n--;
    }

    return cmp;
}

