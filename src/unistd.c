#include "unistd.h"

int isatty(int fd) {
    return fd < 3 ? 1 : 0;
}
