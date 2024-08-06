#include "stdio.h"
#include "stdlib.h"

int main() {
    const char* strings[] = {
        "Hello",
        "Hello, world!",
        "Hello, world! Also, goodbye cruel world!",
        NULL,
    };
    const char** sp = strings;

    while(*sp) {
        char* buf;

        asprintf(&buf, "%s", *sp);
        printf("%s\n", buf);
        free(buf);

        sp++;
    }

    return 0;
}
