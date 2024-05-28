#include "stdio.h"
#include "stdlib.h"

int main() {
    const char* strings[] = {
        /* Plain */
        "1234",
        "-1234",
        "+1234",

        /* Spaces */
        " 1234 ",
        " -1234 ",
        " +1234 ",

        /* Invalid prefix/suffix */
        "1234x",
        "-1234x",
        "+1234x",
        "x1234x",
        "x-1234x",
        "x+1234x",

        /* Invalid */
        "--1234",
        "-+1234",
        "+-1234",
        "0x1234",
        "01234",
        NULL,
    };
    const char** sp = strings;

    while(*sp) {
        printf("%s = %d\n", *sp, atoi(*sp));
        sp++;
    }

    return 0;
}

