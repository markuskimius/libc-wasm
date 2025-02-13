#ifndef _CTYPE_H_
#define _CTYPE_H_

#include "libc-wasm.h"

#ifdef __cplusplus
extern "C" {
#endif


int isdigit(int c);
int isspace(int c);
int isxdigit(int c);
int isprint(int c);
int toupper(int c);
int tolower(int c);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _CTYPE_H_ */
