#include <stdlib.h>
#include "mymalloc.h"

int main() {
    int *p = malloc(sizeof(int) * 4);
    free(p + 1);
}