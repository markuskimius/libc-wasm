#ifndef _LIMITS_H_
#define _LIMITS_H_

#include "libc-wasm.h"

#ifdef __cplusplus
extern "C" {
#endif


#define CHAR_MAX   __SCHAR_MAX__
#define SHRT_MAX   __SHRT_MAX__
#define INT_MAX    __INT_MAX__
#define LONG_MAX   __LONG_MAX__
#define LLONG_MAX  __LONG_LONG_MAX__

#define CHAR_MIN   (-CHAR_MAX-1)
#define SHRT_MIN   (-SHRT_MAX-1)
#define INT_MIN    (-INT_MAX-1)
#define LONG_MIN   (-LONG_MAX-1L)
#define LLONG_MIN  (-LLONG_MAX-1LL)

#define UCHAR_MAX  (CHAR_MAX*2+1)
#define USHRT_MAX  (SHRT_MAX*2+1)
#define UINT_MAX   (INT_MAX*2U+1U)
#define ULONG_MAX  (LONG_MAX*2UL+1UL)
#define ULLONG_MAX (LLONG_MAX*2ULL+1ULL)


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _LIMITS_H_ */
