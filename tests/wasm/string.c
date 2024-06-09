#include "stdio.h"
#include "string.h"

int main() {
    const char* strings[] = {
        "Hello, world!",
        "HELLO, WORLD!",
        "Hello, Bob!",
    };

    for(int i=0; i<sizeof(strings)/sizeof(*strings); i++) {
        const char* s1 = strings[i];

        printf("strlen(%s) => %zu\n", s1, strlen(s1));
        printf("strchr('%s', '%c') => %s\n", s1, 'l', strchr(s1, 'l'));
        printf("strrchr('%s', '%c') => %s\n", s1, 'l', strrchr(s1, 'l'));
    }
    printf("\n");

    for(int i=0; i<sizeof(strings)/sizeof(*strings); i++) {
        for(int j=0; j<sizeof(strings)/sizeof(*strings); j++) {
            const char* s1 = strings[i];
            const char* s2 = strings[j];
            int len = 5;

            printf("strcmp('%s', '%s') => %d\n", s1, s2, strcmp(s1, s2));
            printf("strncmp('%s', '%s', %d) => %d\n", s1, s2, strncmp(s1, s2, len), len);
            printf("strcasecmp('%s', '%s') => %d\n", s1, s2, strcasecmp(s1, s2));
            printf("strncasecmp('%s', '%s', %d) => %d\n", s1, s2, strncasecmp(s1, s2, len), len);
        }

        printf("\n");
    }

    return 0;
}

