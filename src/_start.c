#ifndef _NOSTART_

#include "stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif


/* ***************************************************************************
* DECLARATIONS
*/

extern int __main_void(void);
extern int main(int argc, char* argv[]) __attribute__((weak));


/* ***************************************************************************
* FUNCTIONS
*/

int main(int argc, char* argv[]) {
    return __main_void();
}

void _start() {
    int ret = main(0, 0);
    exit(ret);
}


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _NOSTART_ */
