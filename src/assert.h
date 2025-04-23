#ifndef _ASSERT_H_
#define _ASSERT_H_

#include "stdio.h"
#include "stdlib.h"
#include "libc-wasm.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifdef NDEBUG
#define assert(expr) do {} while(0)
#else
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
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _ASSERT_H_ */
