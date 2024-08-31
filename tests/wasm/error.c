#include "assert.h"
#include "errno.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"

int main() {
    errno = EBADF;

    perror("main");
    printf("%s\n", strerror(errno));

    return 0;
}

