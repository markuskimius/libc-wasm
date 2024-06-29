#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"

int main() {
    char* hello = malloc(strlen("Hello")+1);
    char* world = malloc(strlen("World")+1);
    char* hello2 = NULL;

    strncpy(hello, "Hello", strlen("Hello")+1);
    strncpy(world, "World", strlen("World")+1);

    printf("hello : %s\n", hello);
    printf("world : %s\n", world);

    hello2 = realloc(hello, 1024);
    strncat(hello2, ", world!", 4);
    printf("hello : %s\n", hello2);

    assert(hello != hello2);

    return 0;
}
