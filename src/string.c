#include "string.h"
#include "ctype.h"
#include "errno.h"
#include "inttypes.h"
#include "stdlib.h"

void* memcpy(void* dest, const void* src, size_t n) {
    return __builtin_memcpy(dest, src, n);
}

void* memset(void* s, int c, size_t n) {
    return __builtin_memset(s, c, n);
}

void* memchr(const void* s, int c, size_t n) {
    unsigned const char* cp = s;
    void* result = NULL;

    for(size_t i=0; i<n; i++) {
        if(*cp == c) {
            result = (void*) cp;
            break;
        }

        cp++;
    }

    return result;
}

size_t strlen(const char* s) {
    size_t i = 0;

    while(*s) {
        s++;
        i++;
    }

    return i;
}

char* strchr(const char* s, int c) {
    char* cp = NULL;

    while(1) {
        if(*s == c) { cp = (char*)s; break; }
        if(*s == '\0') break;
        s++;
    }

    return cp;
}

char* strrchr(const char* s, int c) {
    char* cp = NULL;

    while(1) {
        if(*s == c) cp = (char*)s;
        if(*s == '\0') break;
        s++;
    }

    return cp;
}

char* strdup(const char* s) {
    size_t len = strlen(s);
    char* dup = malloc(len+1);

    if(dup) {
        strncpy(dup, s, len+1);
    }

    return dup;
}

char* strncat(char* dest, const char *src, size_t n) {
    char* cp = dest;

    /* Go to the end of dest */
    while(*cp) {
        cp++;
    }

    /* Strcpy */
    while(n>0) {
        *cp = *src;
        if(*src == '\0') break;

        src++;
        cp++;
        n--;
    }

    return dest;
}

char* strncpy(char* dest, const char *src, size_t n) {
    char* cp = dest;

    while(n>0) {
        *cp = *src;
        if(*src == '\0') break;

        src++;
        cp++;
        n--;
    }

    return dest;
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

char* strerror(int errnum) {
    char* text = NULL;

    if(0 <= errnum && errnum < sys_nerr) {
        text = (char*) sys_errlist[errnum];
    }

    return text;
}
