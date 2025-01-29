#include "stdlib.h"
#include "assert.h"
#include "ctype.h"
#include "errno.h"
#include "limits.h"
#include "math.h"
#include "stdint.h"
#include "string.h"
#include "unistd.h"


/* ***************************************************************************
* TYPES
*/

typedef struct _MBINFO {
    struct _MBINFO* prev;
    struct _MBINFO* next;
    int8_t* data;
    size_t size;
    int free;
} _MBINFO;


/* ***************************************************************************
* MACROS
*/

#define _NAN             (0.0 / 0.0)
#define _INF             (1.0 / 0.0)

#define _MBINFO_SIZE     (LIBC_WASM_ALIGN_CEIL(sizeof(_MBINFO)))


/* ***************************************************************************
* GLOBALS
*/

static _MBINFO* _mbi_head = NULL;


/* ***************************************************************************
* PRIVATE FUNCTIONS
*/

static inline _MBINFO* _mbi_new(size_t memsize, _MBINFO* prev, _MBINFO* next) {
    size_t blksize = LIBC_WASM_ALIGN_CEIL(memsize); /* Round up the requested memory size to the next word */
    _MBINFO* mbi = NULL;

    /* Get enough memory for the header + data */
    mbi = sbrk(_MBINFO_SIZE + blksize);

    /* Initialize */
    mbi->prev = prev;
    mbi->next = next;
    mbi->data = ((int8_t*)mbi) + _MBINFO_SIZE;      /* Point to data just beyond the header */
    mbi->size = blksize;
    mbi->free = 1;

    /* Relink */
    if(prev) prev->next = mbi;
    if(next) next->prev = mbi;

    return mbi;
}

static inline void _mbi_split(_MBINFO* mbi, size_t newsize) {
    size_t blksize = LIBC_WASM_ALIGN_CEIL(newsize); /* Round up the requested memory size to the next word */
    ssize_t nextsize = (ssize_t)mbi->size - blksize - _MBINFO_SIZE;

    /*
    * Shrink this block and create a new empty next block, but only if there is
    * enough space for the next block.
    */

    if(nextsize > 0) {
        _MBINFO* mbj = (_MBINFO*)(mbi->data + blksize);
        _MBINFO* mbk = mbi->next;

        /* Initialize */
        mbj->prev = mbi;
        mbj->next = mbk;
        mbj->data = ((int8_t*)mbj) + _MBINFO_SIZE;  /* Point to data just beyond the header */
        mbj->size = nextsize;
        mbj->free = 1;

        /* Relink */
        mbi->next = mbj;
        mbj->prev = mbi;
        mbj->next = mbk;
        if(mbk) mbk->prev = mbj;

        /* Update this block */
        mbi->size = blksize;
    }
}

/**
* Merge this mbi with next.
*/
static inline void _mbi_merge(_MBINFO* mbi) {
    _MBINFO* mbj = mbi->next;

    /* Ensure next block exists and it's contiguous */
    if(mbj && (mbi->data + mbi->size == (int8_t*)mbj)) {
        _MBINFO* mbk = mbj->next;

        assert(mbj->free);

        /* Unlink */
        mbi->next = mbk;
        if(mbk) mbk->prev = mbi;

        /* Change size */
        mbi->size = mbj->data + mbj->size - mbi->data;
    }
}

static inline _MBINFO* _mbi_of(int8_t* memdata) {
    return (_MBINFO*)(memdata - _MBINFO_SIZE);
}


/* ***************************************************************************
* PUBLIC FUNCTIONS
*/

void* calloc(size_t nmemb, size_t size) {
    size_t sizeup = LIBC_WASM_ALIGN_CEIL(size);
    void* mem = malloc(nmemb * sizeup);

    memset(mem, 0, nmemb * sizeup);

    return mem;
}

void* malloc(size_t size) {
    _MBINFO* mbi = _mbi_head;

    assert(size > 0);

    /* Round up requested memory to the next power of 2 */
    // size = LIBC_WASM_ALIGN_CEIL(size);   /* round up to the nearest word instead */
    size = LIBC_WASM_POW2_CEIL(size);

    /* Initialize the head */
    if(_mbi_head == NULL) {
        mbi = _mbi_head = _mbi_new(size, NULL, NULL);
    }

    /* Find the first free block <= size */
    while(mbi->next) {
        if(mbi->free && size <= mbi->size) break;
        mbi = mbi->next;
    }

    /* Allocate a new block if no free block of desired size available */
    if(!mbi->free || size > mbi->size) {
        assert(mbi->next == NULL);
        mbi = _mbi_new(size, mbi, NULL);
    }

    /* Free up memory we don't need */
    _mbi_split(mbi, size);

    /* Flag this block as used */
    mbi->free = 0;

    return mbi->data;
}

void* realloc(void* ptr, size_t size) {
    if(ptr == NULL && size == 0) {
        return NULL;
    }
    else if(ptr == NULL) {
        return malloc(size);
    }
    else if(size == 0) {
        free(ptr);

        return NULL;
    }
    else {
        _MBINFO* mbi = _mbi_of(ptr);
        _MBINFO* mbj = mbi->next;

        /* Resize only if needed */
        if(size <= mbi->size) {
            return mbi->data;
        }

        /* Round up requested memory to the next power of 2 */
        // size = LIBC_WASM_ALIGN_CEIL(size);   /* round up to the nearest word instead */
        size = LIBC_WASM_POW2_CEIL(size);

        /* Ensure next block exists, is contiguous, is free, and big enough */
        if(mbi->next && mbi->next->free && size <= (mbi->size + mbi->next->size) && (mbi->data + mbi->size == (int8_t*)mbj)) {
            _mbi_merge(mbi);
            _mbi_split(mbi, size);  /* Free up memory we don't need */
            return mbi->data;
        }

        /* Allocate new memory */
        if(1) {
            int8_t* newdata = malloc(size);

            /* Copy data */
            memcpy(newdata, mbi->data, mbi->size);
            free(mbi->data);

            return newdata;
        }
    }
}

void free(void* ptr) {
    if(ptr) {
        _MBINFO* mbi = _mbi_of(ptr);

        assert(!mbi->free);

        /* Flag this block as free */
        mbi->free = 1;

        /* Merge with next block if free */
        if(mbi->next && mbi->next->free) {
            _mbi_merge(mbi);
        }

        /* Merge with prev block if free */
        if(mbi->prev && mbi->prev->free) {
            _mbi_merge(mbi->prev);
        }
    }
}

int atoi(const char* nptr) {
    const char* cp = nptr;
    int value = 0;
    int neg = 0;

    /* Skip Whitespaces */
    while(isspace(*cp)) cp++;

    /* Sign */
    if(*cp == '+' || *cp == '-') {
        if(*cp == '-') neg = 1;
        cp++;
    }

    /* Number */
    while(isdigit(*cp)) {
        value *= 10;
        value += (*cp - '0');
        cp++;
    }

    return neg ? -value : value;
}

double atof(const char* nptr) {
    return strtod(nptr, NULL);
}

long int strtol(const char* nptr, char** endptr, int base) {
    long long value = strtoll(nptr, endptr, base);

    if(value < LONG_MIN) {
        errno = ERANGE;
        value = LONG_MIN;
    }
    else if(LONG_MAX < value) {
        errno = ERANGE;
        value = LONG_MAX;
    }

    return value;
}

long long int strtoll(const char* nptr, char** endptr, int base) {
    long long value = 0;
    const char* cp = nptr;
    int isvalid = 0;
    int sign = 1;

    /* Skip spaces */
    while(isspace(*cp)) cp++;

    /* Sign */
    if(*cp == '+' || *cp == '-') {
        if(*cp == '-') sign = -1;
        cp++;
    }

    /* Prefix */
    if((base == 0 || base == 16) && *cp == '0' && tolower(*(cp+1)) == 'x') {
        cp += 2;
        base = 16;
    }
    else if((base == 0 || base == 8) && *cp == '0') {
        cp += 1;
        base = 8;
    }
    else if(base == 0) {
        base = 10;
    }

    /* Value */
    while(*cp) {
        int c = tolower(*cp);
        int digit = 0;
        long long last = value;

        /* Convert */
        if('0' <= c && c <= '9') digit = c - '0';
        else if('a' <= c && c <= 'z') digit = c - 'a' + 10;
        else break;

        /* Validate */
        if(base <= digit) break;

        /* Accumulate */
        value = value * base + sign * digit;
        isvalid = 1;
        cp++;

        /* Check for overflow/underflow */
        if(sign < 0 && last < value) {
            value = LLONG_MIN;
            errno = ERANGE;
            break;
        }
        else if(sign > 0 && value < last) {
            value = LLONG_MAX;
            errno = ERANGE;
            break;
        }
    }

    /* End pointer */
    if(endptr) *endptr = (char*)cp;

    /* Validate */
    if(!isvalid) errno = EINVAL;

    return value;
}

double strtod(const char* nptr, char** endptr) {
    const char* cp = nptr;
    double value = 0.0;
    int isvalid = 0;
    int base = 10;
    int neg = 0;

    /* Skip whitespaces */
    while(isspace(*cp)) cp++;

    /* Sign */
    if(*cp == '+' || *cp == '-') {
        if(*cp == '-') neg = 1;
        cp++;
    }

    /* Infinity */
    if(strncasecmp(cp, "infinity", strlen("infinity")) == 0) {
        cp += strlen("infinity");
        value = _INF;
        isvalid = 1;
    }
    /* Inf */
    else if(strncasecmp(cp, "inf", 3) == 0) {
        cp += strlen("inf");
        value = _INF;
        isvalid = 1;
    }
    /* NaN */
    else if(strncasecmp(cp, "nan", 3) == 0) {
        cp += strlen("nan");
        value = _NAN;
        isvalid = 1;
    }
    /* Normal number */
    else {
        /* Hexadecimal? */
        if(strncasecmp(cp, "0x", 2) == 0) {
            cp += strlen("0x");
            base = 16;
        }

        /* Whole part */
        while(1) {
            if(isdigit(*cp)) {
                value *= base;
                value += (*cp - '0');
                isvalid = 1;
                cp++;
            }
            else if(base == 16 && isxdigit(*cp)) {
                value *= base;
                value += (tolower(*cp) - 'a' + 10);
                isvalid = 1;
                cp++;
            }
            else break;
        }

        /* Overflow check */
        if(isinf(value)) {
            value = HUGE_VAL;
            errno = ERANGE;
        }

        /* Decimal part */
        if(*cp == '.') {
            const char* cp1 = cp;
            double divisor = 1.0;
            size_t ndigit = 0;

            /* Skip '.' */
            cp++;

            /* Number */
            while(1) {
                if(isdigit(*cp)) {
                    value *= base;
                    value += (*cp - '0');
                    divisor *= base;
                    cp++;
                }
                else if(base == 16 && isxdigit(*cp)) {
                    value *= base;
                    value += (tolower(*cp) - 'a' + 10);
                    divisor *= base;
                    cp++;
                }
                else break;

                ndigit++;
                isvalid = 1;
            }

            /* Finalize */
            if(ndigit) value /= divisor;
            else cp = cp1;
        }

        /* Exponent part */
        if((isvalid && base==10 && tolower(*cp)=='e') || (isvalid && base==16 && tolower(*cp)=='p')) {
            const double exp10[] = { 1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10 };
            const double exp2[] = { 0x1p0, 0x1p1, 0x1p2, 0x1p3, 0x1p4, 0x1p5, 0x1p6, 0x1p7, 0x1p8, 0x1p9, 0x1p10 };
            const double* exp = (base==10) ? exp10 : exp2;
            double factor = 1.0;
            int eneg = 0;
            size_t ndigit = 0;
            const char* cp2 = cp;

            /* Skip 'e' or 'p' */
            cp++;

            /* Sign */
            if(*cp == '+' || *cp == '-') {
                if(*cp == '-') eneg = 1;
                cp++;
            }

            /* Number */
            while(isdigit(*cp)) {
                if(eneg) value /= exp[*cp-'0'] * factor;
                else value *= exp[*cp-'0'] * factor;

                factor *= exp[10];
                cp++;
            }
        }
    }

    /* End pointer */
    if(endptr) *endptr = (char*)cp;

    /* Validate */
    if(!isvalid) {
        errno = EINVAL;
        value = 0.0;
        neg = 0;
    }

    return neg ? -value : value;
}

void exit(int status) {
    _exit(status);
}
