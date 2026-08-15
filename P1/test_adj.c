#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main() {
    void *a = malloc(100);
    void *b = malloc(100);
    free(a);
    free(b);

    void *c = malloc(200);
    printf("%p\n", c);
}