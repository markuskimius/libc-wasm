#include "stdlib.h"
#include "assert.h"
#include "ctype.h"
#include "errno.h"
#include "limits.h"
#include "string.h"


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

#define _WORD_T          int32_t
#define _WORD_SIZE       (sizeof(_WORD_T))
#define _WORD_MASK       (_WORD_SIZE-1)
#define _WORD_IMASK      (~_WORD_MASK)
#define _WORD_CEIL(size) (((int32_t)(size)+_WORD_MASK) & _WORD_IMASK)

#define _MBINFO_SIZE     (_WORD_CEIL(sizeof(_MBINFO)))
#define _PAGE_SIZE       (64 * 1024)


/* ***************************************************************************
* GLOBALS
*/

extern int8_t __heap_base;

static int8_t* _heap_base = &__heap_base;
static int8_t* _heap_brk  = &__heap_base;

static _MBINFO* _mbi_head = NULL;


/* ***************************************************************************
* PRIVATE FUNCTIONS
*/

static inline _MBINFO* _mbi_new(size_t memsize, _MBINFO* prev, _MBINFO* next) {
    _MBINFO* mbi = NULL;

    /* Round up the requested memory size to the next word */
    memsize = _WORD_CEIL(memsize);

    /* Get enough memory for the header + data */
    mbi = sbrk(_MBINFO_SIZE + memsize);

    /* Initialize */
    mbi->prev = prev;
    mbi->next = next;
    mbi->data = ((int8_t*)mbi) + _MBINFO_SIZE;  /* Point to data just beyond the header */
    mbi->size = memsize;
    mbi->free = 1;

    /* Relink */
    if(prev) prev->next = mbi;
    if(next) next->prev = mbi;

    return mbi;
}

static inline void _mbi_split(_MBINFO* mbi, size_t newsize) {
    ssize_t nextsize = (ssize_t)mbi->size - newsize - _MBINFO_SIZE;

    /*
    * Shrink this block and create a new empty next block, but only if there is
    * enough space for the next block.
    */

    if(nextsize > 0) {
        _MBINFO* mbj = (_MBINFO*)(mbi->data + _WORD_CEIL(newsize));
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
        mbi->size = _WORD_CEIL(newsize);
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

static uint32_t _memory_size() {
    asm(
        "memory.size 0\n"
        "return\n"
    );

    return 0;
}

static void _memory_grow(int npages) {
    asm(
        "local.get 0\n"
        "memory.grow 0\n"
    );
}


/* ***************************************************************************
* PUBLIC FUNCTIONS
*/

void* sbrk(size_t incr) {
    int8_t* last = _heap_brk;
    size_t memsize = (size_t)_memory_size() * _PAGE_SIZE;

    _heap_brk += _WORD_CEIL(incr);

    /* Grow memory if needed */
    if((size_t)_heap_brk > memsize) {
        int npages = (((size_t)_heap_brk) - memsize + _PAGE_SIZE - 1) / _PAGE_SIZE;

        _memory_grow(npages);
    }

    return last;
}

void* malloc(size_t size) {
    _MBINFO* mbi = _mbi_head;

    assert(size > 0);

    /* Round up requested memory to the nearest word */
    size = _WORD_CEIL(size);

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
    _MBINFO* mbi = _mbi_of(ptr);
    _MBINFO* mbj = mbi->next;

    /* Ensure next block exists, is contiguous, is free, and big enough */
    if(mbi->next && mbi->next->free && mbi->size + mbi->next->size < size && (mbi->data + mbi->size == (int8_t*)mbj)) {
        _mbi_merge(mbi);
        return mbi;
    }

    /* Need to create new memory */
    free(mbi);

    return malloc(size);
}

void free(void* ptr) {
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
    const char* cp = nptr;
    double value = 0.0;
    int base = 10;
    int neg = 0;

    /* Skip Whitespaces */
    while(isspace(*cp)) cp++;

    /* NaN */
    if(strncasecmp(cp, "nan", 3) == 0) {
        return _NAN;
    }

    /* Sign */
    if(*cp == '+' || *cp == '-') {
        if(*cp == '-') neg = 1;
        cp++;
    }

    /* Infinity */
    if(strncasecmp(cp, "inf", 3) == 0) {
        return neg ? -_INF : _INF;
    }

    /* Hexadecimal? */
    if(strncasecmp(cp, "0x", 2) == 0) {
        base = 16;
        cp += 2;
    }

    /* Invalid number? */
    if(base == 10 && !isdigit(*cp)) return 0.0;
    if(base == 16 && !isxdigit(*cp)) return 0.0;

    /* Whole number */
    while(1) {
        if(isdigit(*cp)) {
            value *= base;
            value += (*cp - '0');
            cp++;
        }
        else if(base == 16 && isxdigit(*cp)) {
            value *= base;
            value += (tolower(*cp) - 'a' + 10);
            cp++;
        }
        else break;
    }

    /* Fractional */
    if(*cp == '.') {
        double divisor = 1.0;

        cp++;

        /* Number */
        while(1) {
            if(isdigit(*cp)) {
                divisor *= base;
                value *= base;
                value += (*cp - '0');
                cp++;
            }
            else if(base == 16 && isxdigit(*cp)) {
                divisor *= base;
                value *= base;
                value += (tolower(*cp) - 'a' + 10);
                cp++;
            }
            else break;
        }

        value /= divisor;
    }

    /* Exponent */
    if((base==10 && tolower(*cp)=='e') || (base==16 && tolower(*cp)=='p')) {
        const double exp10[] = { 1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10 };
        const double exp2[] = { 0x1p0, 0x1p1, 0x1p2, 0x1p3, 0x1p4, 0x1p5, 0x1p6, 0x1p7, 0x1p8, 0x1p9, 0x1p10 };
        const double* exp = (base==10) ? exp10 : exp2;
        double factor = 1.0;
        int eneg = 0;

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

    return neg ? -value : value;
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
        if(base < digit) break;

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

void exit(int status) {
    _exit(status);
}
