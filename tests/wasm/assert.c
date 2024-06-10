#include "stdio.h"
#include "assert.h"
#include "math.h"

int main() {
    printf("M_PI = %lf\n", M_PI);

    assert(M_PI < 3.15);
    assert(M_PI < 3.14);

    printf("We shouldn't get here\n");

    return 0;
}
