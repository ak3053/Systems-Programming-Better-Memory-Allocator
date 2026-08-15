#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "mymalloc.h"

#define OPS 120

void workload() {
    void *ptrs[OPS];

    for (int i = 0; i < OPS; i++) {
        void *p = malloc(1);
        free(p);
    }

    for (int i = 0; i < OPS; i++)
        ptrs[i] = malloc(1);

    for (int i = 0; i < OPS; i++)
        free(ptrs[i]);

    int count = 0;
    while (count < OPS) {
        if (rand() % 2 == 0) {
            ptrs[count++] = malloc(1);
        } else if (count > 0) {
            int idx = rand() % count;
            free(ptrs[idx]);
            ptrs[idx] = ptrs[--count];
        }
    }

    while (count > 0)
        free(ptrs[--count]);

    for (int i = 0; i < 50; i++) {
        void *p = malloc(64);
        free(p);
    }

    void *list[50];
    for (int i = 0; i < 50; i++)
        list[i] = malloc(32);

    for (int i = 49; i >= 0; i--)
        free(list[i]);
}

int main() {
    srand(time(NULL));

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < 50; i++)
        workload();

    gettimeofday(&end, NULL);

    double elapsed =
        (end.tv_sec - start.tv_sec) +
        (end.tv_usec - start.tv_usec) / 1e6;

    printf("Average time per workload: %.6f seconds\n", elapsed / 50.0);

    return 0;
}