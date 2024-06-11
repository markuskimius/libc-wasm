#ifndef _STDLIB_H_
#define _STDLIB_H_

#include "inttypes.h"

#ifdef __cplusplus
extern "C" {
#endif


#define NULL ((void*) 0)

void* sbrk(size_t incr);
void free(void* ptr);
void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
double atof(const char* nptr);
int atoi(const char* nptr);
void exit(int status);
__attribute__((import_module("env"), import_name("_exit"))) extern void _exit(int status);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _STDLIB_H_ */
