#include "math.h"
#include "inttypes.h"
#include "stdio.h"

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

double fabs(double x) {
    int64_t* xp = (int64_t*)&x;

    /* Clear the sign bit */
    *xp &= 0x7fffffffffffffff;

    return x;
}

double sqrt(double x) {
    asm(
        "local.get 0\n"
        "f64.sqrt\n"
        "return\n"
    );

    return x;
}

double pow(double x, double y) {
    int64_t* yp = (int64_t*)&y;
    int64_t ye = ((*yp >> 52) & 0x7ff) - 1023;                        /* exponent is 11 bits and 1023-biased */
    int64_t ym = ((*yp & 0xfffffffffffff) | 0x10000000000000) << 11;  /* mantissa is 52 bits + hidden bit; shift MSB to the sign bit */
    double result = 1.0;
    double dp = x;

    /* NaN */
    if(isnan(y)) return y;

    /* Subnormal exponent's hidden bit is 0 */
    if(ye == -1023 && !isinf(y)) {
        ye = -1022;
        ym &= (0xfffffffffffff << 11);
    }

    /* Adjust for strictly-decimal exponent */
    if(ye < 0) dp = sqrt(dp);

    /* Whole part of the exponent */
    while(ye >= 0) {
        result *= result;
        if(ym < 0) result *= x;

        ym <<= 1;
        ye--;
    }

    /* Decimal part of the exponent */
    while(ym) {
        dp = sqrt(dp);
        if(ym < 0) result *= dp;

        ym <<= 1;
    }

    /* Negative exponent */
    if(*yp < 0) result = 1.0/result;

    return result;
}

double round(double x) {
    int64_t* xp = (int64_t*)&x;

    /*
    * For some reason f64.nearest does not round up .5 number, so we simulate
    * round using ceil and floor.
    */

    if(*xp < 0) return ceil(x - 0.5);
    else return floor(x + 0.5);
}

double floor(double x) {
    asm(
        "local.get 0\n"
        "f64.floor\n"
        "return\n"
    );

    return x;
}

double ceil(double x) {
    asm(
        "local.get 0\n"
        "f64.ceil\n"
        "return\n"
    );

    return x;
}
