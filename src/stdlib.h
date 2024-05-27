#ifndef _STDLIB_H_
#define _STDLIB_H_

#include "inttypes.h"

#ifdef __cplusplus
extern "C" {
#endif


#define NULL ((void*) 0)

void exit(int status);
void* sbrk(size_t incr);
void free(void* ptr);
void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
double atof(const char* nptr);
int atoi(const char* nptr);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _STDLIB_H_ */
