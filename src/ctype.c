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
