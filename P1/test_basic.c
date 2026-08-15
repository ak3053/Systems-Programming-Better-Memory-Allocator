#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main() {
    int *p = malloc(sizeof(int));
    *p = 42;
    printf("%d\n", *p);
    free(p);
    return 0;
}