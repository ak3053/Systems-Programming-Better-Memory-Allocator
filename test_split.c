#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main() {
    void *p1 = malloc(100);
    void *p2 = malloc(100);
    printf("%p %p\n", p1, p2);
    free(p1);
    free(p2);
}