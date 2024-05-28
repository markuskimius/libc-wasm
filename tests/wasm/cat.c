#include "stdio.h"
#include "unistd.h"

int main() {
    while(1) {
        int c = fgetc(stdin);

        if(c == EOF) break;
        write(1, &c, 1);
    }

    return 0;
}
