#ifndef _STRING_H_
#define _STRING_H_

#include "inttypes.h"

#ifdef __cplusplus
extern "C" {
#endif


void* memcpy(void* dest, const void* src, size_t n);
void* memset(void* s, int c, size_t n);
size_t strlen(const char* s);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _STRING_H_ */
