#include "ctype.h"


int isdigit(int c) {
    return '0' <= c && c <= '9';
}

int isspace(int c) {
    int itis = 0;

    switch(c) {
        case ' ' :
        case '\f':
        case '\n':
        case '\r':
        case '\t':
        case '\v':
            itis = 1; break;
    }

    return itis;
}

int isxdigit(int c) {
    return isdigit(c) || 'a' <= c && c <= 'f' || 'A' <= c && c <= 'F' ;
}

int toupper(int c) {
    const int lookup[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    const int index = c - 'a';

    if(0 <= index && index < (sizeof(lookup)/sizeof(*lookup))) {
        c = lookup[index];
    }

    return c;
}

int tolower(int c) {
    const int lookup[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    const int index = c - 'A';

    if(0 <= index && index < (sizeof(lookup)/sizeof(*lookup))) {
        c = lookup[index];
    }

    return c;
}
