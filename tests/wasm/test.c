#include <stdio.h>

int main() {
    double nan = 0.0 / 0.0;
    double inf = 1.0 / 0.0;
    double ninf = -1.0 / 0.0;

    printf("nan = %lf, %d\n", nan, (int)nan);
    printf("inf = %lf, %d\n", inf, (int)inf);
    printf("ninf = %lf, %d\n", ninf, (int)ninf);

    return 0;
}

