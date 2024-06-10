#include "stdio.h"
#include "stdlib.h"

void test() {
    printf("start\n");
    exit(7);
    printf("end\n");
}

int main() {
    test();

    return 0;
}

