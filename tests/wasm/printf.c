#include "stdio.h"
#include "limits.h"
#include "math.h"

#define INF  (1.0 / 0.0)
#define NINF (-1.0 / 0.0)

int main() {
    int ivalues[] = { 0, 789, -789 };
    double fvalues[] = { 0.0, -0.0, 789.0123456789, -789.0123456789, -12345678901234567890.123456789, INF, NINF, NAN };

    printf("STRING TEST\n");
    printf("|Hello, world!|\n");
    printf("|Hello, %s!|\n", "world");
    printf("|%s, %s!|\n", "Hello", "world");
    printf("\n");

    printf("ESCAPE TEST\n");
    printf("%% : |%%|\n");
    printf("\\t : |\t|\n");
    printf("\\v : |\v|\n");
    printf("\\a : |\a|\n");
    printf("\\b : |\b|\n");
    printf("\\r : |\r|\n");
    printf("\n");

    printf("CHARACTER TEST\n");
    printf("H : |%c|\n", 'H');
    printf("\n");

    printf("MULTI-PRINT TEST\n");
    printf("%d, %d, %d, %d\n", 1, 2, 3, 4);
    printf("%s, %d, %s, %d\n", "Hello", 2, "World!", 4);
    printf("%c, %d, %c, %d\n", 'H', 2, 'W', 4);
    printf("%s, %d, %c, %d\n", "Hello", 2, 'W', 4);
    printf("\n");

    for(int i=0; i<sizeof(ivalues)/sizeof(*ivalues); i++) {
        int j = ivalues[i];

        printf("INTEGER TEST (INTEGER=%d)\n", j);

        printf("%%d     : |%d|\n", j);
        printf("%%i     : |%i|\n", j);
        printf("%%u     : |%u|\n", j);
        printf("%%x     : |%x|\n", j);
        printf("%%+d    : |%+d|\n", j);
        printf("%%+i    : |%+i|\n", j);
        printf("%%-d    : |%-d|\n", j);
        printf("%%-i    : |%-i|\n", j);
        printf("%%-u    : |%-u|\n", j);
        printf("%%-x    : |%-x|\n", j);
        printf("%%2d    : |%2d|\n", j);
        printf("%%2i    : |%2i|\n", j);
        printf("%%2u    : |%2u|\n", j);
        printf("%%2x    : |%2x|\n", j);
        printf("%%+2d   : |%+2d|\n", j);
        printf("%%+2i   : |%+2i|\n", j);
        printf("%%-2d   : |%-2d|\n", j);
        printf("%%-2i   : |%-2i|\n", j);
        printf("%%-2u   : |%-2u|\n", j);
        printf("%%-2x   : |%-2x|\n", j);
        printf("%%02d   : |%02d|\n", j);
        printf("%%02i   : |%02i|\n", j);
        printf("%%02u   : |%02u|\n", j);
        printf("%%02x   : |%02x|\n", j);
        printf("%%+02d  : |%+02d|\n", j);
        printf("%%+02i  : |%+02i|\n", j);
        printf("%%4d    : |%4d|\n", j);
        printf("%%4i    : |%4i|\n", j);
        printf("%%4u    : |%4u|\n", j);
        printf("%%4x    : |%4x|\n", j);
        printf("%%+4d   : |%+4d|\n", j);
        printf("%%+4i   : |%+4i|\n", j);
        printf("%%-4d   : |%-4d|\n", j);
        printf("%%-4i   : |%-4i|\n", j);
        printf("%%-4u   : |%-4u|\n", j);
        printf("%%-4x   : |%-4x|\n", j);
        printf("%%04d   : |%04d|\n", j);
        printf("%%04i   : |%04i|\n", j);
        printf("%%04u   : |%04u|\n", j);
        printf("%%04x   : |%04x|\n", j);
        printf("%%+04d  : |%+04d|\n", j);
        printf("%%+04i  : |%+04i|\n", j);
        printf("%%12d   : |%12d|\n", j);
        printf("%%12i   : |%12i|\n", j);
        printf("%%12u   : |%12u|\n", j);
        printf("%%12x   : |%12x|\n", j);
        printf("%%+12d  : |%+12d|\n", j);
        printf("%%+12i  : |%+12i|\n", j);
        printf("%%-12d  : |%-12d|\n", j);
        printf("%%-12i  : |%-12i|\n", j);
        printf("%%-12u  : |%-12u|\n", j);
        printf("%%-12x  : |%-12x|\n", j);
        printf("%%012d  : |%012d|\n", j);
        printf("%%012i  : |%012i|\n", j);
        printf("%%012u  : |%012u|\n", j);
        printf("%%012x  : |%012x|\n", j);
        printf("%%+012d : |%+012d|\n", j);
        printf("%%+012i : |%+012i|\n", j);
        printf("\n");
    }

    for(int i=0; i<sizeof(ivalues)/sizeof(*ivalues); i++) {
        long long j = ivalues[i];

        printf("LONG LONG TEST (LONG LONG=%lld)\n", j);

        printf("%%lld     : |%lld|\n", j);
        printf("%%lli     : |%lli|\n", j);
        printf("%%llu     : |%llu|\n", j);
        printf("%%llx     : |%llx|\n", j);
        printf("%%+lld    : |%+lld|\n", j);
        printf("%%+lli    : |%+lli|\n", j);
        printf("%%-lld    : |%-lld|\n", j);
        printf("%%-lli    : |%-lli|\n", j);
        printf("%%-llu    : |%-llu|\n", j);
        printf("%%-llx    : |%-llx|\n", j);
        printf("%%2lld    : |%2lld|\n", j);
        printf("%%2lli    : |%2lli|\n", j);
        printf("%%2llu    : |%2llu|\n", j);
        printf("%%2llx    : |%2llx|\n", j);
        printf("%%+2lld   : |%+2lld|\n", j);
        printf("%%+2lli   : |%+2lli|\n", j);
        printf("%%-2lld   : |%-2lld|\n", j);
        printf("%%-2lli   : |%-2lli|\n", j);
        printf("%%-2llu   : |%-2llu|\n", j);
        printf("%%-2llx   : |%-2llx|\n", j);
        printf("%%02lld   : |%02lld|\n", j);
        printf("%%02lli   : |%02lli|\n", j);
        printf("%%02llu   : |%02llu|\n", j);
        printf("%%02llx   : |%02llx|\n", j);
        printf("%%+02lld  : |%+02lld|\n", j);
        printf("%%+02lli  : |%+02lli|\n", j);
        printf("%%4lld    : |%4lld|\n", j);
        printf("%%4lli    : |%4lli|\n", j);
        printf("%%4llu    : |%4llu|\n", j);
        printf("%%4llx    : |%4llx|\n", j);
        printf("%%+4lld   : |%+4lld|\n", j);
        printf("%%+4lli   : |%+4lli|\n", j);
        printf("%%-4lld   : |%-4lld|\n", j);
        printf("%%-4lli   : |%-4lli|\n", j);
        printf("%%-4llu   : |%-4llu|\n", j);
        printf("%%-4llx   : |%-4llx|\n", j);
        printf("%%04lld   : |%04lld|\n", j);
        printf("%%04lli   : |%04lli|\n", j);
        printf("%%04llu   : |%04llu|\n", j);
        printf("%%04llx   : |%04llx|\n", j);
        printf("%%+04lld  : |%+04lld|\n", j);
        printf("%%+04lli  : |%+04lli|\n", j);
        printf("%%12lld   : |%12lld|\n", j);
        printf("%%12lli   : |%12lli|\n", j);
        printf("%%12llu   : |%12llu|\n", j);
        printf("%%12llx   : |%12llx|\n", j);
        printf("%%+12lld  : |%+12lld|\n", j);
        printf("%%+12lli  : |%+12lli|\n", j);
        printf("%%-12lld  : |%-12lld|\n", j);
        printf("%%-12lli  : |%-12lli|\n", j);
        printf("%%-12llu  : |%-12llu|\n", j);
        printf("%%-12llx  : |%-12llx|\n", j);
        printf("%%012lld  : |%012lld|\n", j);
        printf("%%012lli  : |%012lli|\n", j);
        printf("%%012llu  : |%012llu|\n", j);
        printf("%%012llx  : |%012llx|\n", j);
        printf("%%+012lld : |%+012lld|\n", j);
        printf("%%+012lli : |%+012lli|\n", j);
        printf("\n");
    }

    for(int i=0; i<sizeof(ivalues)/sizeof(*ivalues); i++) {
        long long j = ivalues[i];

        printf("LONG LONG TEST (LONG LONG=%lld)\n", j);

        printf("%%lld     : |%lld|\n", j);
        printf("%%lli     : |%lli|\n", j);
        printf("%%llu     : |%llu|\n", j);
        printf("%%llx     : |%llx|\n", j);
        printf("%%+lld    : |%+lld|\n", j);
        printf("%%+lli    : |%+lli|\n", j);
        printf("%%-lld    : |%-lld|\n", j);
        printf("%%-lli    : |%-lli|\n", j);
        printf("%%-llu    : |%-llu|\n", j);
        printf("%%-llx    : |%-llx|\n", j);
        printf("%%2lld    : |%2lld|\n", j);
        printf("%%2lli    : |%2lli|\n", j);
        printf("%%2llu    : |%2llu|\n", j);
        printf("%%2llx    : |%2llx|\n", j);
        printf("%%+2lld   : |%+2lld|\n", j);
        printf("%%+2lli   : |%+2lli|\n", j);
        printf("%%-2lld   : |%-2lld|\n", j);
        printf("%%-2lli   : |%-2lli|\n", j);
        printf("%%-2llu   : |%-2llu|\n", j);
        printf("%%-2llx   : |%-2llx|\n", j);
        printf("%%02lld   : |%02lld|\n", j);
        printf("%%02lli   : |%02lli|\n", j);
        printf("%%02llu   : |%02llu|\n", j);
        printf("%%02llx   : |%02llx|\n", j);
        printf("%%+02lld  : |%+02lld|\n", j);
        printf("%%+02lli  : |%+02lli|\n", j);
        printf("%%4lld    : |%4lld|\n", j);
        printf("%%4lli    : |%4lli|\n", j);
        printf("%%4llu    : |%4llu|\n", j);
        printf("%%4llx    : |%4llx|\n", j);
        printf("%%+4lld   : |%+4lld|\n", j);
        printf("%%+4lli   : |%+4lli|\n", j);
        printf("%%-4lld   : |%-4lld|\n", j);
        printf("%%-4lli   : |%-4lli|\n", j);
        printf("%%-4llu   : |%-4llu|\n", j);
        printf("%%-4llx   : |%-4llx|\n", j);
        printf("%%04lld   : |%04lld|\n", j);
        printf("%%04lli   : |%04lli|\n", j);
        printf("%%04llu   : |%04llu|\n", j);
        printf("%%04llx   : |%04llx|\n", j);
        printf("%%+04lld  : |%+04lld|\n", j);
        printf("%%+04lli  : |%+04lli|\n", j);
        printf("%%12lld   : |%12lld|\n", j);
        printf("%%12lli   : |%12lli|\n", j);
        printf("%%12llu   : |%12llu|\n", j);
        printf("%%12llx   : |%12llx|\n", j);
        printf("%%+12lld  : |%+12lld|\n", j);
        printf("%%+12lli  : |%+12lli|\n", j);
        printf("%%-12lld  : |%-12lld|\n", j);
        printf("%%-12lli  : |%-12lli|\n", j);
        printf("%%-12llu  : |%-12llu|\n", j);
        printf("%%-12llx  : |%-12llx|\n", j);
        printf("%%012lld  : |%012lld|\n", j);
        printf("%%012lli  : |%012lli|\n", j);
        printf("%%012llu  : |%012llu|\n", j);
        printf("%%012llx  : |%012llx|\n", j);
        printf("%%+012lld : |%+012lld|\n", j);
        printf("%%+012lli : |%+012lli|\n", j);
        printf("\n");
    }

    for(int i=0; i<sizeof(fvalues)/sizeof(*fvalues); i++) {
        double j = fvalues[i];

        printf("DOUBLE TEST (DOUBLE=%lf)\n", j);

        printf("%%lf      : |%lf|\n", j);
        printf("%%0lf     : |%0lf|\n", j);
        printf("%%1lf     : |%1lf|\n", j);
        printf("%%5lf     : |%5lf|\n", j);
        printf("%%6lf     : |%6lf|\n", j);
        printf("%%7lf     : |%7lf|\n", j);
        printf("%%15lf    : |%15lf|\n", j);
        printf("%%0.0lf   : |%0.0lf|\n", j);
        printf("%%1.0lf   : |%1.0lf|\n", j);
        printf("%%5.0lf   : |%5.0lf|\n", j);
        printf("%%6.0lf   : |%6.0lf|\n", j);
        printf("%%7.0lf   : |%7.0lf|\n", j);
        printf("%%15.0lf  : |%15.0lf|\n", j);
        printf("%%0.1lf   : |%0.1lf|\n", j);
        printf("%%1.1lf   : |%1.1lf|\n", j);
        printf("%%5.1lf   : |%5.1lf|\n", j);
        printf("%%6.1lf   : |%6.1lf|\n", j);
        printf("%%7.1lf   : |%7.1lf|\n", j);
        printf("%%10f     : |%10f|\n", j);
        printf("%%10f     : |%10f|\n", j);
        printf("%%10f     : |%10f|\n", j);
        printf("%%010f    : |%010f|\n", j);
        printf("%%010f    : |%010f|\n", j);
        printf("%%010f    : |%010f|\n", j);
        printf("%%+10f    : |%+10f|\n", j);
        printf("%%+10f    : |%+10f|\n", j);
        printf("%%+10f    : |%+10f|\n", j);
        printf("%%-10f    : |%-10f|\n", j);
        printf("%%-10f    : |%-10f|\n", j);
        printf("%%-10f    : |%-10f|\n", j);
        printf("%%+010f   : |%+010f|\n", j);
        printf("%%+010f   : |%+010f|\n", j);
        printf("%%+010f   : |%+010f|\n", j);
        printf("%%15.1lf  : |%15.1lf|\n", j);
        printf("%%0.10lf  : |%0.10lf|\n", j);
        printf("%%1.10lf  : |%1.10lf|\n", j);
        printf("%%5.10lf  : |%5.10lf|\n", j);
        printf("%%6.10lf  : |%6.10lf|\n", j);
        printf("%%7.10lf  : |%7.10lf|\n", j);
        printf("%%15.10lf : |%15.10lf|\n", j);
        printf("%%0.20lf  : |%0.20lf|\n", j);
        printf("%%1.20lf  : |%1.20lf|\n", j);
        printf("%%5.20lf  : |%5.20lf|\n", j);
        printf("%%6.20lf  : |%6.20lf|\n", j);
        printf("%%7.20lf  : |%7.20lf|\n", j);
        printf("%%15.20lf : |%15.20lf|\n", j);
        printf("\n");
    }

    printf("DOUBLE TEST (DOUBLE=%lf)\n", M_PI);
    printf("%%.1000lf  : |%.1000lf|\n", M_PI);
    printf("%%1000.500lf  : |%1000.500lf|\n", M_PI);
    printf("%%01000.500lf  : |%01000.500lf|\n", M_PI);
    printf("\n");

    return 0;
}

