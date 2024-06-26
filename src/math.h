#ifndef _MATH_H_
#define _MATH_H_

#ifdef __cplusplus
extern "C" {
#endif


#define NAN  (0.0 / 0.0)
#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923078
#define HUGE_VAL (__builtin_huge_val())

int isnan(double x);
int isinf(double x);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _MATH_H_ */
