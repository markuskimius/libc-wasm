#include "stdio.h"
#include "math.h"

#define _NAN  (0.0 / 0.0)
#define _INF  (1.0 / 0.0)
#define _NINF (-1.0 / 0.0)

int main() {
    double values[] = { 0.0, -0.0, 3.141592, -3.141592, 4, -4, 12.4, -12.4, 12.5, -12.5, 12.6, -12.6, _NAN, _INF, _NINF };

    for(int i=0; i<sizeof(values)/sizeof(*values); i++) {
        double x = values[i];

        printf("%10lf : ceil=%lf floor=%lf round=%lf isinf=%d isnan=%d fabs=%lf sqrt=%lf\n", x, ceil(x), floor(x), round(x), isinf(x), isnan(x), fabs(x), sqrt(x));
    }

    return 0;
}

