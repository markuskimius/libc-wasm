#include "stdio.h"

int main() {
    printf("sizeof(char)      : %zd\n", sizeof(char));
    printf("sizeof(short)     : %zd\n", sizeof(short));
    printf("sizeof(int)       : %zd\n", sizeof(int));
    printf("sizeof(long)      : %zd\n", sizeof(long));
    printf("sizeof(long long) : %zd\n", sizeof(long long));
    printf("sizeof(size_t)    : %zd\n", sizeof(size_t));
    printf("sizeof(void*)     : %zd\n", sizeof(void*));

    return 0;
}
