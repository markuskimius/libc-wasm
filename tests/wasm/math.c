#include "stdio.h"
#include "math.h"

#define _NAN  (0.0 / 0.0)
#define _INF  (1.0 / 0.0)
#define _NINF (-1.0 / 0.0)

int main() {
    double values[] = { _NAN, _INF, _NINF, 3.141592 };

    for(int i=0; i<sizeof(values)/sizeof(*values); i++) {
        double v = values[i];

        printf("%10lf : isinf=%d isnan=%d\n", v, isinf(v), isnan(v));
    }

    return 0;
}

