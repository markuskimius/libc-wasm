#include "stdio.h"
#include "ctype.h"

int main() {
    const char* string = "AaFfGgZz09@ ";

    for(const char* cp=string; *cp; cp++) printf("isdigit('%c')  => %d\n", *cp, isdigit(*cp));
    for(const char* cp=string; *cp; cp++) printf("isspace('%c')  => %d\n", *cp, isspace(*cp));
    for(const char* cp=string; *cp; cp++) printf("isxdigit('%c') => %d\n", *cp, isxdigit(*cp));
    for(const char* cp=string; *cp; cp++) printf("toupper('%c')  => %c\n", *cp, toupper(*cp));
    for(const char* cp=string; *cp; cp++) printf("tolower('%c')  => %c\n", *cp, tolower(*cp));

    return 0;
}

