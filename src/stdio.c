#include "stdio.h"
#include "errno.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"


/* ***************************************************************************
* TYPES
*/

typedef struct _FORMAT {
    int altform;
    int zeropad;
    int lalign;
    int sign;
    int ucase;
    int base;
    int width;
    int dwidth;
    int length;
} _FORMAT;


/* ***************************************************************************
* GLOBALS
*/

static char _sbufs[3][1024];
static FILE _streams[3] = {
    { 0, _sbufs[0], sizeof(_sbufs[0]), 't' },
    { 1, _sbufs[1], sizeof(_sbufs[1]), 't' },
    { 2, _sbufs[2], sizeof(_sbufs[2]), 't' },
};

FILE* stdin = &_streams[0];
FILE* stdout = &_streams[1];
FILE* stderr = &_streams[2];


/* ***************************************************************************
* _FORMAT FUNCTIONS
*/

/**
* Parse the modifier(s) after % and before the conversion specifier.
*
* @param cp  Pointer to the format string after %.
* @param fmt Parsed modifiers are saved here.
* @returns   Pointer to the conversion specifier just after the modifiers.
*/
static const char* _fparse(const char* cp, _FORMAT* fmt) {
    int dot = 0;

    memset(fmt, 0, sizeof(*fmt));
    fmt->base = 10;
    fmt->dwidth = 6;

    while(*cp) {
        int32_t handled = 1;

        switch(*cp) {
            case '#': fmt->altform = 1; break;
            case '-': fmt->lalign = 1; break;
            case '+': fmt->sign = '+'; break;
            case ' ': fmt->sign = ' '; break;
            case '.': dot = 1; fmt->dwidth = 0; break;
            case '0': if(dot) fmt->dwidth *= 10; else if(fmt->width) fmt->width *= 10; else fmt->zeropad = 1; break;
            case '1': if(dot) fmt->dwidth = fmt->dwidth * 10 + 1; else fmt->width = fmt->width * 10 + 1; break;
            case '2': if(dot) fmt->dwidth = fmt->dwidth * 10 + 2; else fmt->width = fmt->width * 10 + 2; break;
            case '3': if(dot) fmt->dwidth = fmt->dwidth * 10 + 3; else fmt->width = fmt->width * 10 + 3; break;
            case '4': if(dot) fmt->dwidth = fmt->dwidth * 10 + 4; else fmt->width = fmt->width * 10 + 4; break;
            case '5': if(dot) fmt->dwidth = fmt->dwidth * 10 + 5; else fmt->width = fmt->width * 10 + 5; break;
            case '6': if(dot) fmt->dwidth = fmt->dwidth * 10 + 6; else fmt->width = fmt->width * 10 + 6; break;
            case '7': if(dot) fmt->dwidth = fmt->dwidth * 10 + 7; else fmt->width = fmt->width * 10 + 7; break;
            case '8': if(dot) fmt->dwidth = fmt->dwidth * 10 + 8; else fmt->width = fmt->width * 10 + 8; break;
            case '9': if(dot) fmt->dwidth = fmt->dwidth * 10 + 9; else fmt->width = fmt->width * 10 + 9; break;
            case 'l': fmt->length = (fmt->length == sizeof(long)) ? sizeof(long long) : sizeof(long); break;
            case 'z': fmt->length = sizeof(size_t); break;
            default : handled = 0; break;
        }

        if(!handled) break;
        cp++;
    }

    return cp;
}


/* ***************************************************************************
* FILE FUNCTIONS
*/

static inline void _finit(FILE* stream, char* buf, size_t bufsize, int fd, char mode) {
    memset(stream, 0, sizeof(*stream));

    stream->fd = fd;
    stream->buf = buf;
    stream->size = bufsize;
    stream->mode = mode;
}

static size_t _fgetc(FILE* stream, char* cp) {
    size_t nchar = 0;

    if(stream->index >= stream->end) {
        ssize_t count = read(stream->fd, stream->buf, stream->size);

        stream->index = 0;
        stream->end = count;

        if(count == 0) stream->eof = 1;
    }

    if(stream->index < stream->end) {
        *cp = stream->buf[stream->index++];
        nchar++;
    }

    return nchar;
}

static size_t _fputc(FILE* stream, char c) {
    size_t nchar = 0;

    if(stream->index == stream->size) fflush(stream);

    if(stream->index < stream->size) {
        stream->buf[stream->index++] = c;
        nchar++;
    }

    if(c == '\n' && stream->mode == 't') fflush(stream);

    return nchar;
}

static size_t _fputcr(FILE* stream, char c, size_t count) {
    size_t nchar = 0;

    while(nchar < count && _fputc(stream, c)) {
        nchar++;
    }

    return nchar;
}

static size_t _fputs(FILE* stream, const char* s) {
    size_t nchar = 0;

    while(*s && _fputc(stream, *s++)) {
        nchar++;
    }

    return nchar;
}

static size_t _fnputs(FILE* stream, const char* s, size_t count) {
    size_t nchar = 0;

    while(*s && nchar < count && _fputc(stream, *s++)) {
        nchar++;
    }

    return nchar;
}


/* ***************************************************************************
* STRING FUNCTIONS
*/

static void _sprintc(char* dest, _FORMAT* fmt, char c) {
    dest[0] = c;
    dest[1] = '\0';
}

static size_t _sprintu(char* dest, _FORMAT* fmt, uintmax_t value) {
    uintmax_t div = value / fmt->base;
    int rem = value % fmt->base;
    size_t nchar = 0;

    /* Higher digits */
    if(div) nchar += _sprintu(dest, fmt, div);

    /* Lowest digit */
    if(rem < 10) dest[nchar++] = rem + '0';
    else if(fmt->ucase) dest[nchar++] = rem - 10 + 'A';
    else dest[nchar++] = rem - 10 + 'a';

    return nchar;
}

static size_t _sprinti(char* dest, _FORMAT* fmt, intmax_t value) {
    size_t zloc = 0;
    size_t nchar = 0;

    /* Strip high bits for numbers < sizeof(intmax_t) */
    if(fmt->sign == 'u' && fmt->length < sizeof(intmax_t)) {
        switch(fmt->length) {
            case sizeof(int8_t)  : value &= 0xff; break;
            case sizeof(int16_t) : value &= 0xffff; break;
            default              : value &= 0xffffffff; break;
        }
    }

    /* Add sign */
    if(fmt->sign != 'u') {
        /* - for a negative number */
        if(value < 0) {
            dest[nchar++] = '-';
            value = -value;
        }
        /* + or space in place of sign, if requested */
        else if(fmt->sign) {
            dest[nchar++] = fmt->sign;
        }
    }

    /* Add altform prefix */
    if(fmt->altform) {
        char x = fmt->ucase ? 'X' : 'x';

        switch(fmt->base) {
            case 8: dest[nchar++] = '0'; break;                     /* 0 prefix for octal */
            case 16: dest[nchar++] = '0'; dest[nchar++] = x; break; /* 0x prefix for hexadecimal */
        }
    }

    /*
    * This is where we would want to add zero padding but a large padding can
    * cause dest to overflow so we defer the padding responsibility to the
    * caller.
    */
    zloc = nchar;

    /* Number part */
    nchar += _sprintu(&dest[nchar], fmt, value);

    /* Terminator */
    dest[nchar] = '\0';

    return zloc;
}

static size_t _snprintf(char* dest, size_t size, _FORMAT* fmt, double value) {
    int64_t* vp = (int64_t*)&value;
    size_t zloc = 0;
    size_t nchar = 0;

    /* Round */
    value += (*vp<0?-1:1) * 0.5 * pow(fmt->base, -fmt->dwidth);

    /* - for a negative number; check the sign bit to handle -0.0 */
    if(*vp < 0) {
        dest[nchar++] = '-';
        value = -value;
    }
    /* + or space in place of sign, if requested, and for a non-NaN */
    else if(fmt->sign && !isnan(value)) {
        dest[nchar++] = fmt->sign;
    }

    /*
    * This is where we would want to add zero padding but a large padding can
    * cause dest to overflow so we defer the padding responsibility to the
    * caller.
    */
    zloc = nchar;

    /* NaN */
    if(isnan(value)) {
        dest[nchar++] = 'n';
        dest[nchar++] = 'a';
        dest[nchar++] = 'n';
        fmt->zeropad = 0;
    }
    /* Info */
    else if(isinf(value)) {
        dest[nchar++] = 'i';
        dest[nchar++] = 'n';
        dest[nchar++] = 'f';
        fmt->zeropad = 0;
    }
    /* Normal number */
    else {
        /* Whole part */
        if(1) {
            size_t ndigits = 1;
            double save = value;

            /* Reduce to single digit */
            while(value >= fmt->base) {
                value /= fmt->base;
                ndigits++;
            }

            /* Print one digit at a time */
            while(ndigits > 0) {
                int rem = value;

                if(rem < 10) dest[nchar++] = rem + '0';
                else if(fmt->ucase) dest[nchar++] = rem - 10 + 'A';
                else dest[nchar++] = rem - 10 + 'a';

                value -= rem;
                value *= fmt->base;
                ndigits--;
            }

            value = save;
        }

        /* Decimal part */
        if(fmt->dwidth > 0) {
            double frac = value - floor(value);

            /* assert(frac <= 0); */
            dest[nchar++] = '.';

            for(size_t i=0; i<fmt->dwidth && i<size-1; i++) {
                int rem = (int)(frac * fmt->base) % fmt->base;

                frac = frac * fmt->base - rem;

                if(rem < 10) dest[nchar++] = rem + '0';
                else if(fmt->ucase) dest[nchar++] = rem - 10 + 'A';
                else dest[nchar++] = rem - 10 + 'a';
            }
        }
    }

    /* Terminator */
    dest[nchar] = '\0';

    return zloc;
}


/* ***************************************************************************
* PUBLIC FUNCTIONS
*/

int fileno(FILE* stream) {
    return stream->fd;
}

int feof(FILE* stream) {
    return stream->eof;
}

int ferror(FILE* stream) {
    return stream->err;
}

void clearerr(FILE* stream) {
    stream->err = 0;
}

int fflush(FILE* stream) {
    int flushed = EOF;

    if(stream->fd < 0) {
        stream->eof = flushed = EOF;
        stream->err = errno = EBADF;
    }
    else {
        flushed = write(stream->fd, stream->buf, stream->index);
        stream->index = 0;
    }

    return flushed;
}

int fgetc(FILE* stream) {
    char c;
    size_t nchar = _fgetc(stream, &c);

    return nchar ? ((int)c & 0xff) : EOF;
}

int fputc(int c, FILE* stream) {
    size_t nchar = _fputc(stream, c);

    return nchar ? nchar : EOF;
}

size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    char* cp = ptr;
    size_t count = 0;

    while(count < nmemb) {
        int nchar = 0;

        for(size_t i=0; i<size; i++) {
            nchar += _fgetc(stream, cp++);
        }

        if(nchar) count++;
        else break;
    }

    return count;
}

size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream) {
    const char* cp = ptr;
    size_t count = 0;

    while(count < nmemb) {
        int nchar = 0;

        for(size_t i=0; i<size; i++) {
            nchar += _fputc(stream, *cp++);
        }

        if(nchar) count++;
        else break;
    }

    return count;
}

int printf(const char *format, ...) {
    va_list ap;
    int nc;

    va_start(ap, format);
    nc = vprintf(format, ap);
    va_end(ap);

    return nc;
}

int fprintf(FILE* stream, const char* format, ...) {
    va_list ap;
    int nc;

    va_start(ap, format);
    nc = vfprintf(stream, format, ap);
    va_end(ap);

    return nc;
}

int snprintf(char* str, size_t size, const char* format, ...) {
    va_list ap;
    int nc;

    va_start(ap, format);
    nc = vsnprintf(str, size, format, ap);
    va_end(ap);

    return nc;
}

int vprintf(const char* format, va_list ap) {
    return vfprintf(stdout, format, ap);
}

int vfprintf(FILE* stream, const char* format, va_list ap) {
    const char* cp = format;
    int32_t nchar = 0;
    _FORMAT fmt;

    while(*cp) {
        char buf[320];  /* Longest double that can be printed */
        char* bp = buf;
        ssize_t len = 0, ilen = 0, dlen = 0;
        int32_t zloc = 0;
        char* svalue = NULL;
        intmax_t ivalue = 0;
        double fvalue = 0;
        int cvalue = 0;

        /* Plain character */
        if(*cp != '%') {
            nchar += _fputc(stream, *cp++);
            continue;
        }

        /* Save the modifier(s) into stream->fmt, increment cp */
        cp = _fparse(cp+1, &fmt);

        /* Get value */
        switch(*cp) {
            case '%': cvalue = '%';                break;
            case 'c': cvalue = va_arg(ap, int);    break;
            case 's': svalue = va_arg(ap, char*);  break;
            case 'f': fvalue = va_arg(ap, double); break;
            case 'i': case 'd': case 'o': case 'u': case 'x': case 'X': case 'p':
                switch(fmt.length) {
                    case sizeof(long long): ivalue = va_arg(ap, long long); break;
                    case sizeof(long)     : ivalue = va_arg(ap, long); break;
                    default               : ivalue = va_arg(ap, int); break;
                }
                break;
        }

        /* Print the value */
        switch(*cp) {
            case '%': _sprintc(bp, &fmt, cvalue);      break;
            case 'c': _sprintc(bp, &fmt, 0x01);        break; /* 0x01 is a placeholder; actual character (cvalue) is printed later */
            case 's': bp = svalue ? svalue : "(null)"; break; /* Point to the input */
            case 'f':                                                 zloc = _snprintf(bp, sizeof(buf), &fmt, fvalue); break;
            case 'i': fmt.base = 10;                                  zloc = _sprinti(bp, &fmt, ivalue); break;
            case 'd': fmt.base = 10;                                  zloc = _sprinti(bp, &fmt, ivalue); break;
            case 'o': fmt.base = 8 ; fmt.sign = 'u';                  zloc = _sprinti(bp, &fmt, ivalue); break;
            case 'u': fmt.base = 10; fmt.sign = 'u';                  zloc = _sprinti(bp, &fmt, ivalue); break;
            case 'x': fmt.base = 16; fmt.sign = 'u';                  zloc = _sprinti(bp, &fmt, ivalue); break;
            case 'X': fmt.base = 16; fmt.sign = 'u'; fmt.ucase = 1;   zloc = _sprinti(bp, &fmt, ivalue); break;
            case 'p': fmt.base = 16; fmt.sign = 'u'; fmt.altform = 1; zloc = _sprinti(bp, &fmt, ivalue); break;
            default : return -1;
        }

        /*
        * Calculate the printed length so we know how much to pad on the left.
        * We need to handle floating points specially because the floating
        * point may be padded to the right as well.  Other types can just use
        * the string length.
        */
        if(*cp == 'f') {
            const char* fp = bp;

            /* Integer part */
            while(*fp && *fp != '.') {
                ilen++;
                len++;
                fp++;
            }

            /* Decimal part */
            if(*fp == '.') {
                len += fmt.dwidth + 1;  /* +1 for '.'; len is the ideal length */
                fp++;

                while(*fp) {
                    dlen++;             /* dlen is the actual length from _snprintf */
                    fp++;
                }
            }
        }
        else {
            len = strlen(bp);
        }

        /* Left pad with spaces */
        if(len < fmt.width && !fmt.lalign && !fmt.zeropad) {
            nchar += _fputcr(stream, ' ', fmt.width - len);
        }

        /* Zero pad */
        if(len < fmt.width && !fmt.lalign && fmt.zeropad) {
            nchar += _fnputs(stream, bp, zloc);  /* Print characters in front of zeropad */
            bp = &bp[zloc];                      /* Move the pointer to the zeropad location */

            /* Print zero pad */
            nchar += _fputcr(stream, '0', fmt.width - len);
        }

        /*
        * Print the variable.  We handle characters specially because the
        * character we want to print may be '\0'.
        */
        if(*cp == 'c') nchar += _fputc(stream, cvalue);
        else nchar += _fputs(stream, bp);

        /*
        * Right pad a floating point number with zeros.  This is necessary if
        * the caller could request a large decimal precision be printed; our
        * buffer has a size limit so _snprintf() only populates decimals up to
        * the limit of the buffer.  This is where we supplement the buffer with
        * the additional precision requested by the caller with 0's.  We also
        * need to take care to avoid adding zero right padding if the result is
        * "nan" or "inf" which we can test with dlen > 0.
        */
        if(*cp == 'f' && 0 < dlen && dlen < fmt.dwidth) {
            nchar += _fputcr(stream, '0', fmt.dwidth - dlen);
        }

        /* Right pad with spaces */
        if(len < fmt.width && fmt.lalign) {
            nchar += _fputcr(stream, ' ', fmt.width - len);
        }

        cp++;
    }

    /* Flush the buffer to the file descriptor, if any */
    fflush(stream);

    /* Terminate the string (NUL is not included in nchar) */
    if(stream->index < stream->size) stream->buf[stream->index] = '\0';
    else {
        stream->buf[stream->size-1] = '\0';
        nchar--;
    }

    return nchar;
}

int vsnprintf(char* str, size_t size, const char* format, va_list ap) {
    FILE file;

    _finit(&file, str, size, -1, 't');

    return vfprintf(&file, format, ap);
}
