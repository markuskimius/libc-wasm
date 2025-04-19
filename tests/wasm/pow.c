#include "stdio.h"
#include "math.h"

#define _NAN  (0.0 / 0.0)
#define _INF  (1.0 / 0.0)
#define _NINF (-1.0 / 0.0)

int main() {
    double values[] = { 0.0, -0.0, 3.0, -3.0, 3.141592, -3.141592, 4.0, -4.0, _NAN, _INF, _NINF };

    for(int i=0; i<sizeof(values)/sizeof(*values); i++) {
        for(int j=0; j<sizeof(values)/sizeof(*values); j++) {
            double x = values[i];
            double y = values[j];

            printf("pow(%lf,%lf) -> %lf\n", x, y, pow(x,y));
        }
    }

    printf("pow(%lf,%lf) -> %lf\n", 3.0, 0.25 , pow(3.0, 0.25));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, 6.103, pow(7.0, 6.103));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, 4.125, pow(7.0, 4.125));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, 3.25 , pow(7.0, 3.25));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, 1.5  , pow(7.0, 1.5));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, 0.0  , pow(7.0, 0.0));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, 0.5  , pow(7.0, 0.5));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, 0.375, pow(7.0, 0.375));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, 0.25 , pow(7.0, 0.25));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, 0.125, pow(7.0, 0.125));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, 0.103, pow(7.0, 0.103));

    printf("pow(%lf,%lf) -> %lf\n", -3.0, 0.25 , pow(-3.0, 0.25));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, 6.103, pow(-7.0, 6.103));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, 4.125, pow(-7.0, 4.125));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, 3.25 , pow(-7.0, 3.25));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, 1.5  , pow(-7.0, 1.5));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, 0.0  , pow(-7.0, 0.0));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, 0.5  , pow(-7.0, 0.5));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, 0.375, pow(-7.0, 0.375));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, 0.25 , pow(-7.0, 0.25));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, 0.125, pow(-7.0, 0.125));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, 0.103, pow(-7.0, 0.103));

    printf("pow(%lf,%lf) -> %lf\n", 3.0, -0.25 , pow(3.0, -0.25));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, -6.103, pow(7.0, -6.103));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, -4.125, pow(7.0, -4.125));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, -3.25 , pow(7.0, -3.25));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, -1.5  , pow(7.0, -1.5));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, -0.0  , pow(7.0, -0.0));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, -0.5  , pow(7.0, -0.5));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, -0.375, pow(7.0, -0.375));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, -0.25 , pow(7.0, -0.25));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, -0.125, pow(7.0, -0.125));
    printf("pow(%lf,%lf) -> %lf\n", 7.0, -0.103, pow(7.0, -0.103));

    printf("pow(%lf,%lf) -> %lf\n", -3.0, -0.25 , pow(-3.0, -0.25));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, -6.103, pow(-7.0, -6.103));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, -4.125, pow(-7.0, -4.125));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, -3.25 , pow(-7.0, -3.25));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, -1.5  , pow(-7.0, -1.5));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, -0.0  , pow(-7.0, -0.0));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, -0.5  , pow(-7.0, -0.5));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, -0.375, pow(-7.0, -0.375));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, -0.25 , pow(-7.0, -0.25));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, -0.125, pow(-7.0, -0.125));
    printf("pow(%lf,%lf) -> %lf\n", -7.0, -0.103, pow(-7.0, -0.103));

    return 0;
}

