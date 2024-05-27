#include "stdlib.h"
#include "assert.h"


/* ***************************************************************************
* TYPES
*/

typedef struct MBINFO {
    struct MBINFO* prev;
    struct MBINFO* next;
    int8_t* data;
    size_t size;
    int free;
} MBINFO;


/* ***************************************************************************
* MACROS
*/

#define WORD_T          int32_t
#define WORD_SIZE       (sizeof(WORD_T))
#define WORD_MASK       (WORD_SIZE-1)
#define WORD_IMASK      (~WORD_MASK)
#define WORD_CEIL(size) (((int32_t)(size)+WORD_MASK) & WORD_IMASK)

#define MBINFO_SIZE     (WORD_CEIL(sizeof(MBINFO)))


/* ***************************************************************************
* GLOBALS
*/

extern int8_t __heap_base;

static int8_t* heap_base = &__heap_base;
static int8_t* heap_brk  = &__heap_base;

static MBINFO* mbi_head = NULL;


/* ***************************************************************************
* PRIVATE FUNCTIONS
*/

static inline MBINFO* mbi_new(size_t memsize, MBINFO* prev, MBINFO* next) {
    MBINFO* mbi = NULL;

    /* Round up the requested memory size to the next word */
    memsize = WORD_CEIL(memsize);

    /* Get enough memory for the header + data */
    mbi = sbrk(MBINFO_SIZE + memsize);

    /* Initialize */
    mbi->prev = prev;
    mbi->next = next;
    mbi->data = ((int8_t*)mbi) + MBINFO_SIZE;  /* Point to data just beyond the header */
    mbi->size = memsize;
    mbi->free = 1;

    /* Relink */
    if(prev) prev->next = mbi;
    if(next) next->prev = mbi;

    return mbi;
}

static inline void mbi_split(MBINFO* mbi, size_t newsize) {
    size_t nextsize = mbi->size - newsize - MBINFO_SIZE;

    /*
    * Shrink this block and create a new empty next block, but only if there is
    * enough space for the next block.
    */

    if(nextsize > 0) {
        MBINFO* mbj = (MBINFO*)(mbi->data + WORD_CEIL(newsize));
        MBINFO* mbk = mbi->next;

        /* Initialize */
        mbj->prev = mbi;
        mbj->next = mbk;
        mbj->data = ((int8_t*)mbj) + MBINFO_SIZE;  /* Point to data just beyond the header */
        mbj->size = nextsize;
        mbj->free = 1;

        /* Relink */
        mbi->next = mbj;
        mbj->prev = mbi;
        mbj->next = mbk;
        if(mbk) mbk->prev = mbj;

        /* Update this block */
        mbi->size = WORD_CEIL(newsize);
    }
}

/**
* Merge this mbi with next.
*/
static inline void mbi_merge(MBINFO* mbi) {
    MBINFO* mbj = mbi->next;

    /* Ensure the next block exists and it's contiguous */
    if(mbj && (mbi->data + mbi->size == (int8_t*)mbj)) {
        MBINFO* mbk = mbj->next;

        assert(mbi->free && mbj->free);

        /* Unlink */
        mbi->next = mbk;
        if(mbk) mbk->prev = mbi;

        /* Change size */
        mbi->size = mbj->data + mbj->size - mbi->data;
    }
}

static inline MBINFO* mbi_of(int8_t* memdata) {
    return (MBINFO*)(memdata - MBINFO_SIZE);
}


/* ***************************************************************************
* PUBLIC FUNCTIONS
*/

void* sbrk(size_t incr) {
    int8_t* last = heap_brk;

    heap_brk += WORD_CEIL(incr);

    return last;
}

void* malloc(size_t size) {
    MBINFO* mbi = mbi_head;

    assert(size > 0);

    /* Round up requested memory to the nearest word */
    size = WORD_CEIL(size);

    /* Initialize the head */
    if(mbi_head == NULL) {
        mbi = mbi_head = mbi_new(size, NULL, NULL);
    }

    /* Find the first free block <= size */
    while(mbi->next) {
        if(mbi->free && size <= mbi->size) break;
        mbi = mbi->next;
    }

    /* Allocate a new block if no free block of desired size available */
    if(!mbi->free || size > mbi->size) {
        assert(mbi->next == NULL);
        mbi = mbi_new(size, mbi, NULL);
    }

    /* Free up memory we don't need */
    mbi_split(mbi, size);

    /* Flag this block as used */
    mbi->free = 0;

    return mbi->data;
}

void free(void* ptr) {
    MBINFO* mbi = mbi_of(ptr);

    assert(!mbi->free);

    /* Flag this block as free */
    mbi->free = 1;

    /* Merge with next block if free */
    if(mbi->next && mbi->next->free) {
        mbi_merge(mbi);
    }

    /* Merge with prev block if free */
    if(mbi->prev && mbi->prev->free) {
        mbi_merge(mbi->prev);
    }
}

void* realloc(void* ptr, size_t size) {
// TODO
    return NULL;
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
// TODO
    return 0;
}








