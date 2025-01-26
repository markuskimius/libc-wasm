#include "stdio.h"
#include "limits.h"
#include "inttypes.h"

int main() {
    printf("sizeof(char)      : %zd\n", sizeof(char));
    printf("sizeof(short)     : %zd\n", sizeof(short));
    printf("sizeof(int)       : %zd\n", sizeof(int));
    printf("sizeof(long)      : %zd\n", sizeof(long));
    printf("sizeof(long long) : %zd\n", sizeof(long long));
    printf("sizeof(size_t)    : %zd\n", sizeof(size_t));
    printf("sizeof(void*)     : %zd\n", sizeof(void*));

    printf("sizeof(int8_t)    : %zd\n", sizeof(int8_t));
    printf("sizeof(int16_t)   : %zd\n", sizeof(int16_t));
    printf("sizeof(int32_t)   : %zd\n", sizeof(int32_t));
    printf("sizeof(int64_t)   : %zd\n", sizeof(int64_t));
    printf("sizeof(intmax_t)  : %zd\n", sizeof(intmax_t));

    printf("sizeof(uint8_t)   : %zd\n", sizeof(uint8_t));
    printf("sizeof(uint16_t)  : %zd\n", sizeof(uint16_t));
    printf("sizeof(uint32_t)  : %zd\n", sizeof(uint32_t));
    printf("sizeof(uint64_t)  : %zd\n", sizeof(uint64_t));
    printf("sizeof(uintmax_t) : %zd\n", sizeof(uintmax_t));

    printf("CHAR_MAX          : %d\n", CHAR_MAX);
    printf("SHRT_MAX          : %d\n", SHRT_MAX);
    printf("INT_MAX           : %d\n", INT_MAX);
    printf("LONG_MAX          : %ld\n", LONG_MAX);
    printf("LLONG_MAX         : %lld\n", LLONG_MAX);

    printf("CHAR_MIN          : %d\n", CHAR_MIN);
    printf("SHRT_MIN          : %d\n", SHRT_MIN);
    printf("INT_MIN           : %d\n", INT_MIN);
    printf("LONG_MIN          : %ld\n", LONG_MIN);
    printf("LLONG_MIN         : %lld\n", LLONG_MIN);

    printf("UCHAR_MAX         : %u\n", UCHAR_MAX);
    printf("USHRT_MAX         : %u\n", USHRT_MAX);
    printf("UINT_MAX          : %u\n", UINT_MAX);
    printf("ULONG_MAX         : %lu\n", ULONG_MAX);
    printf("ULLONG_MAX        : %llu\n", ULLONG_MAX);

    return 0;
}
