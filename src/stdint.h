#ifndef _STDINT_H_
#define _STDINT_H_

#include "libc-wasm.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef __INT8_TYPE__       int8_t;
typedef __INT16_TYPE__      int16_t;
typedef __INT32_TYPE__      int32_t;
typedef __INT64_TYPE__      int64_t;
typedef __INTMAX_TYPE__     intmax_t;
typedef __UINT8_TYPE__      uint8_t;
typedef __UINT16_TYPE__     uint16_t;
typedef __UINT32_TYPE__     uint32_t;
typedef __UINT64_TYPE__     uint64_t;
typedef __UINTMAX_TYPE__    uintmax_t;


#define INT8_C(x)           x
#define INT16_C(x)          x
#define INT32_C(x)          x
#define INT64_C(x)          x ## LL
#define UINT8_C(x)          x
#define UINT16_C(x)         x
#define UINT32_C(x)         x ## U
#define UINT64_C(x)         x ## ULL


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _STDINT_H_ */
