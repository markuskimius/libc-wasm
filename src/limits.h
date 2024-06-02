#ifndef _LIMITS_H_
#define _LIMITS_H_

#ifdef __cplusplus
extern "C" {
#endif


#define CHAR_MIN   (-128)
#define CHAR_MAX   127
#define SHRT_MIN   (-32768)
#define SHRT_MAX   32767
#define INT_MIN    (-INT_MAX-1)
#define INT_MAX    2147483647
#define LONG_MIN   (-LONG_MAX-1L)
#define LONG_MAX   2147483647L
#define LLONG_MIN  (-LLONG_MAX-1LL)
#define LLONG_MAX  9223372036854775807LL
#define UCHAR_MAX  255
#define USHRT_MAX  65535
#define UINT_MAX   4294967295U
#define ULONG_MAX  4294967295UL
#define ULLONG_MAX 18446744073709551615ULL


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _LIMITS_H_ */
