#ifndef _STDLIB_H_
#define _STDLIB_H_

#include "inttypes.h"

#ifdef __cplusplus
extern "C" {
#endif


#define NULL ((void*) 0)

__attribute__((export_name("sbrk"))) void* sbrk(size_t incr);
__attribute__((export_name("malloc"))) void* malloc(size_t size);
__attribute__((export_name("realloc"))) void* realloc(void* ptr, size_t size);
__attribute__((export_name("free"))) void free(void* ptr);

int atoi(const char* nptr);
double atof(const char* nptr);
long int strtol(const char* nptr, char** endptr, int base);
long long int strtoll(const char* nptr, char** endptr, int base);
double strtod(const char* nptr, char** endptr);

__attribute__((import_module("env"), import_name("_exit"))) extern void _exit(int status);
void exit(int status);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _STDLIB_H_ */
