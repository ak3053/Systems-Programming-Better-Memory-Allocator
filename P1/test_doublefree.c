#include <stdlib.h>
#include "mymalloc.h"

int main() {
    int *p = malloc(100);
    free(p);
    free(p);
}