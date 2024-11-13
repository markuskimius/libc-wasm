#ifndef _STDIO_H_
#define _STDIO_H_

#include <stdarg.h>
#include "inttypes.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    int fd;
    char* buf;
    size_t size;
    char mode;
    int index;
    int end;

    int eof;
    int err;
} FILE;

extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;

int feof(FILE* stream);
int fgetc(FILE* stream);
int fputc(int c, FILE* stream);
int fileno(FILE* stream);
int ferror(FILE* stream);
int fflush(FILE *stream);
int putchar(int c);
int puts(const char* s);
int fputs(const char* s, FILE* stream);
void clearerr(FILE* stream);
size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);

int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);
int asprintf(char** strp, const char* format, ...);
int vprintf(const char *format, va_list ap);
int vfprintf(FILE *stream, const char *format, va_list ap);
int vsnprintf(char *str, size_t size, const char *format, va_list ap);
int vasprintf(char** strp, const char* format, va_list ap);

void perror(const char* s);


#define EOF       -1
#define getc(s)   fgetc(s)
#define putc(c,s) fputc(c,s)


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _STDIO_H_ */
