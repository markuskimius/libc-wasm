#include "stdio.h"
#include "math.h"

#define _NAN  (0.0 / 0.0)
#define _INF  (1.0 / 0.0)
#define _NINF (-1.0 / 0.0)

int main() {
    double values[] = { 0.0, -0.0, 3.141592, -3.141592, 4, _NAN, _INF, _NINF };

    for(int i=0; i<sizeof(values)/sizeof(*values); i++) {
        double x = values[i];

        printf("%10lf : isinf=%d isnan=%d fabs=%lf sqrt=%lf\n", x, isinf(x), isnan(x), fabs(x), sqrt(x));
    }

    return 0;
}

