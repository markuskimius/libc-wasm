#include "stdio.h"
#include "inttypes.h"

int main() {
    double values[] = {
        0.0,
        -0.0,
        1.0,
        -1.0,
        0.0 / 0.0,
        1.0 / 0.0,
        -1.0 / 0.0,
    };

    for(int i=0; i<sizeof(values)/sizeof(*values); i++) {
        double v = values[i];

        if(v < 0.0 || (v == 0.0 && *(int64_t*)&v)) printf("%+lf = negative\n", v);
        else printf("%+lf = positive\n", v);
    }

    return 0;
}

