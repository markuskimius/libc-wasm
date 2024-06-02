#ifndef _STRING_H_
#define _STRING_H_

#include "inttypes.h"

#ifdef __cplusplus
extern "C" {
#endif


void* memcpy(void* dest, const void* src, size_t n);
void* memset(void* s, int c, size_t n);
size_t strlen(const char* s);
int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
int strcasecmp(const char* s1, const char* s2);
int strncasecmp(const char* s1, const char* s2, size_t n);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _STRING_H_ */
