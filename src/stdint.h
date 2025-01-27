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


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _STDINT_H_ */
