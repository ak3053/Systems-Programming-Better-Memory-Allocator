#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mymalloc.h"

int main() {
    void *p = malloc(1);
    printf("Address: %p\n", p);
    printf("Alignment: %ld\n", (long)p % 8);
    free(p);
}