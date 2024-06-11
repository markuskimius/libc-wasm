#include "stdlib.h"
#include "start.h"

#ifndef _NOSTART_

int main(int argc, char* argv[]) {
    return __main_void();
}

void _start() {
    int ret = main(0, 0);
    exit(ret);
}

#endif /* _NOSTART_ */
