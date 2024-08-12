#include "ctype.h"
#include "stdio.h"

int main() {
    for(int i=0x00; i<0x80; i+=0x10) {
        for(int j=0x00; j<0x10; j++) {
            printf("%d", isprint(i+j));
        }
        printf("\n");
    }

    return 0;
}

