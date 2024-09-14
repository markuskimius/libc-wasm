#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"

int main() {
    char* hello;
    char* world;


    hello = malloc(3);
    printf("hello = %p\n", hello);

    hello = realloc(hello, 17);
    printf("hello = %p\n", hello);

    hello = realloc(hello, 47);
    printf("hello = %p\n", hello);


    world = malloc(3);
    printf("world = %p\n", world);

    world = realloc(world, 17);
    printf("world = %p\n", world);

    world = realloc(world, 47);
    printf("world = %p\n", world);

    free(hello);
    free(world);
    printf("\n");


    hello = malloc(3);
    printf("hello = %p\n", hello);

    world = malloc(3);
    printf("world = %p\n", world);

    hello = realloc(hello, 17);
    printf("hello = %p\n", hello);

    world = realloc(world, 17);
    printf("world = %p\n", world);

    hello = realloc(hello, 47);
    printf("hello = %p\n", hello);

    world = realloc(world, 47);
    printf("world = %p\n", world);

    free(hello);
    free(world);
    printf("\n");


    hello = malloc(3);
    printf("hello = %p\n", hello);

    hello = realloc(hello, 17);
    printf("hello = %p\n", hello);

    hello = realloc(hello, 47);
    printf("hello = %p\n", hello);


    world = malloc(3);
    printf("world = %p\n", world);

    world = realloc(world, 17);
    printf("world = %p\n", world);

    world = realloc(world, 47);
    printf("world = %p\n", world);

    free(hello);
    free(world);
    printf("\n");


    return 0;
}
