#include "stdio.h"
#include "stdlib.h"
#include "inttypes.h"

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
    char buf[65];
    const char* strings[] = {
        /* Plain */
        "1234",
        "-1234",
        "+1234",

        /* Special */
        "3.14159265359",
        "-1.234e-3",
        "-0xa.aaa",
        "-0xa.aaap-3",
        "Inf",
        "-Inf",
        "NaN",

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
        double v = atof(*sp);
        double v2 = strtod(*sp, NULL);

        printf("%15s => %15lf (%s)\n", *sp, v, sprintb(buf, v));
        printf("%15s => %15lf (%s)\n", *sp, v2, sprintb(buf, v2));
        sp++;
    }

    return 0;
}

