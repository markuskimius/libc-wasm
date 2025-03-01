#include "stdio.h"
#include "stdlib.h"
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
        printf("strchr('%s', '%c') => %s\n", s1, '\0', strchr(s1, '\0'));
        printf("strrchr('%s', '%c') => %s\n", s1, '\0', strrchr(s1, '\0'));
    }
    printf("\n");

    for(int i=0; i<sizeof(strings)/sizeof(*strings); i++) {
        char* dup = strdup(strings[i]);

        for(int j=i; j<sizeof(strings)/sizeof(*strings); j++) {
            const char* s1 = dup;
            const char* s2 = strings[j];

            printf("('%s'=='%s') => %d\n", s1, s2, s1==s2);
            printf("strcmp('%s', '%s') => %d\n", s1, s2, strcmp(s1, s2));
        }

        free(dup);
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

    {
        unsigned char target[1234];
        unsigned char source[1234];
        int i = 0;

        printf("memset ... ");
        memset(source, 0xc5, sizeof(source));

        for(i=0; i<sizeof(source); i++) {
            if(source[i] != 0xc5) {
                printf("[ERR]\n");
                break;
            }
        }

        if(i == sizeof(source)) printf("[OK]\n");

        for(i=0; i<sizeof(source); i++) {
            source[i] = i & 0xff;
        }

        printf("memcpy ... ");
        memcpy(target, source, sizeof(target));

        for(i=0; i<sizeof(source); i++) {
            if(target[i] != source[i]) {
                printf("[ERR]\n");
                break;
            }
        }

        if(i == sizeof(source)) printf("[OK]\n");

        printf("memmove ... ");
        memmove(target, target+1, sizeof(target)-1);

        for(i=0; i<sizeof(source)-1; i++) {
            if(target[i] != source[i+1]) {
                printf("[ERR]\n");
                break;
            }
        }

        if(i == sizeof(source)-1) printf("[OK]\n");
    }

    return 0;
}

