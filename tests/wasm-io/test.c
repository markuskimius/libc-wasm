#include "stdio.h"

__attribute__((export_name("shout"))) int shout(const char* text1, const char* text2) {
    return printf("%s, %s!\n", text1, text2);
}

int main() {
    return 0;
}
