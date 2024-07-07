#include "math.h"
#include "inttypes.h"

int isnan(double x) {
    int64_t* xp = (int64_t*)&x;
    int64_t xe = (*xp >> 52) & 0x7ff;   /* exponent */
    int64_t xm = *xp & 0xfffffffffffff; /* mantissa */

    return (xe==0x7ff) && (xm!=0);
}

int isinf(double x) {
    int64_t* xp = (int64_t*)&x;
    int64_t xe = (*xp >> 52) & 0x7ff;   /* exponent */
    int64_t xm = *xp & 0xfffffffffffff; /* mantissa */

    return (xe==0x7ff) && (xm==0);
}
