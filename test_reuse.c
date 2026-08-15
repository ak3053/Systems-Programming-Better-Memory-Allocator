#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main() {
    void *p1 = malloc(64);
    free(p1);
    void *p2 = malloc(64);
    printf("%p %p\n", p1, p2);
}