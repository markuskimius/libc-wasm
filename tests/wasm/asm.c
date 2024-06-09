#include "stdio.h"

const char* value = "world";

void hello(const char* value) {
    printf("Hello, %s!\n", value);
}

int main() {
    asm(
        "i32.const value\n"
        "i32.load 0\n"
        "call hello\n"
    );

    return 0;
}

