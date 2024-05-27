#ifndef _ASSERT_H_
#define _ASSERT_H_

#include "stdio.h"

#ifdef __cplusplus
extern "C" {
#endif


#define assert(expr) do {                           \
/*    if(!(expr)) {                                  */ \
/*        puts("BAD ASSERT in " __FILE__ " line ");  */ \
/*        puti(__LINE__);                            */ \
/*        puts(": `");                               */ \
/*        puts(#expr "`\n");                         */ \
/*    }                                              */ \
} while(0)


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _ASSERT_H_ */
