#include "unistd.h"

int isatty(int fd) {
    /* FIXME */
    return fd < 3 ? 1 : 0;
}
