#ifndef _ASSERT_H_
#define _ASSERT_H_

#include "stdio.h"
#include "stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif


#define assert(expr) do {                                               \
    if(!(expr)) {                                                       \
        fprintf(stderr,                                                 \
            "Assertion failed: (%s), function %s, file %s, line %d.\n", \
            #expr, __FUNCTION__, __FILE__, __LINE__                     \
        );                                                              \
        fprintf(stderr, "Abort\n");                                     \
        _exit(134);                                                     \
    }                                                                   \
} while(0)


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _ASSERT_H_ */
