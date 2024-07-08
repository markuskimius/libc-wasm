#include "stdio.h"
#include "stdlib.h"

int main() {
    const char* strings[] = {
        /* Plain */
        "1234",
        "-1234",
        "+1234",

        /* Large */
        "9223372036854775807",
        "-9223372036854775808",

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
    int bases[] = { 0, 8, 10, 16 };

    while(*sp) {
        printf("%s = %d\n", *sp, atoi(*sp));

        for(int i=0; i<sizeof(bases)/sizeof(*bases); i++) {
            int base = bases[i];

            printf("%s = %lld\n", *sp, strtoll(*sp, NULL, base));
        }

        printf("\n");
        sp++;
    }

    return 0;
}

