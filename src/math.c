#include "math.h"
#include "inttypes.h"

static const double _nan = 0.0 / 0.0;
static const double _inf = 1.0 / 0.0;
static const double _ninf = -1.0 / 0.0;


int isnan(double x) {
    uint64_t* np = (uint64_t*)&_nan;
    uint64_t* xp = (uint64_t*)&x;

    return *np == *xp;
}

int isinf(double x) {
    uint64_t* ip = (uint64_t*)&_inf;
    uint64_t* np = (uint64_t*)&_ninf;
    uint64_t* xp = (uint64_t*)&x;

    if(*ip == *xp) return 1;
    if(*np == *xp) return -1;

    return 0;
}
