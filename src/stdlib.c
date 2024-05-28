#include "stdlib.h"
#include "assert.h"
#include "ctype.h"


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

#define _WORD_T          int32_t
#define _WORD_SIZE       (sizeof(_WORD_T))
#define _WORD_MASK       (_WORD_SIZE-1)
#define _WORD_IMASK      (~_WORD_MASK)
#define _WORD_CEIL(size) (((int32_t)(size)+_WORD_MASK) & _WORD_IMASK)

#define _MBINFO_SIZE     (_WORD_CEIL(sizeof(_MBINFO)))


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
    size_t nextsize = mbi->size - newsize - _MBINFO_SIZE;

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


/* ***************************************************************************
* PUBLIC FUNCTIONS
*/

void* sbrk(size_t incr) {
    int8_t* last = _heap_brk;

    _heap_brk += _WORD_CEIL(incr);

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

void exit(int status) {
// TODO
    __builtin_unreachable();
}

double atof(const char* nptr) {
// TODO
    return 0;
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
