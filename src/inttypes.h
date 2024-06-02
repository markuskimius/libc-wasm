#ifndef _INTTYPES_H_
#define _INTTYPES_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef char                int8_t;
typedef short               int16_t;
typedef int                 int32_t;
typedef long long           int64_t;
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;
typedef long                ssize_t;
typedef unsigned long       size_t;
typedef int64_t             intmax_t;
typedef uint64_t            uintmax_t;

#define YYSIZE_T size_t


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _INTTYPES_H_ */
