#include "math.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

char* sprintb(char* str, double d) {
    uint64_t v = *(uint64_t*)&d;
    int i = 0;

    for(i=0; i<64; i++) {
        int bit = (v >> (63-i)) & 1;

        str[i] = bit + '0';
    }

    str[i] = '\0';

    return str;
}

int main() {
    double inf = 1.0 / 0.0;

    printf("pow(-inf,3.141592)  -> %lf\n", pow(-inf,3.141592));
    printf("pow(-inf,-3.141592) -> %lf\n", pow(-inf,-3.141592));

    return 0;
}

