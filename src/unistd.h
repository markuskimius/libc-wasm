#ifndef _UNISTD_H_
#define _UNISTD_H_

#include "stddef.h"
#include "libc-wasm.h"
#include "sys/types.h"

#ifdef __cplusplus
extern "C" {
#endif


int isatty(int fd);
__attribute__((export_name("sbrk"))) void* sbrk(size_t incr);
__attribute__((import_module("env"), import_name("read"))) extern ssize_t read(int fd, void* buf, size_t count);
__attribute__((import_module("env"), import_name("write"))) extern ssize_t write(int fd, const void* buf, size_t count);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _UNISTD_H_ */
