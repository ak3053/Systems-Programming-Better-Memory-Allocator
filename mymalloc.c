#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "mymalloc.h"
#define MEMLENGTH 4096
#define ALIGN8(x) (((x) + 7) & ~7)



typedef struct {

    size_t size;

    int allocated;

} header;




static union {
    char bytes[MEMLENGTH];
    double not_used;
} heap;


static int initialized = 0;

static void initialize_heap();
static void shimerge();




static header *find_chunk(void *ptr);
static void leak_detector();


static void initialize_heap() {
    header *h = (header *)heap.bytes;
    h->size = MEMLENGTH;
    h->allocated = 0;
    atexit(leak_detector);
    initialized = 1;
}


static header *next_chunk(header *h) {
    return (header *)((char *)h + h->size);
}


void *mymalloc(size_t size, char *file, int line) {
    if (!initialized) initialize_heap();

    if (size == 0) return NULL;

    size = ALIGN8(size);
    size_t total = size + sizeof(header);

    header *curr = (header *)heap.bytes;

    while ((char *)curr < heap.bytes + MEMLENGTH) {
        if (!curr->allocated && curr->size >= total) {

            if (curr->size - total >= sizeof(header) + 8) {
                header *split = (header *)((char *)curr + total);
                split->size = curr->size - total;
                split->allocated = 0;
                curr->size = total;
            }

            curr->allocated = 1;
            return (char *)curr + sizeof(header);
        }

        curr = next_chunk(curr);
    }

    fprintf(stderr,
            "malloc: Unable to allocate %zu bytes (%s:%d)\n",
            size, file, line);
    return NULL;
}




static header *find_chunk(void *ptr) {
    header *curr = (header *)heap.bytes;

    while ((char *)curr < heap.bytes + MEMLENGTH) {
        if ((char *)curr + sizeof(header) == ptr)
            return curr;
        curr = next_chunk(curr);
    }
    return NULL;
}





void myfree(void *ptr, char *file, int line) {
    if (!ptr) {
        fprintf(stderr, "free: Inappropriate pointer (%s:%d)\n", file, line);
        exit(2);
    }

    if (!initialized) initialize_heap();

    header *h = find_chunk(ptr);

    if (!h || !h->allocated) {
        fprintf(stderr, "free: Inappropriate pointer (%s:%d)\n", file, line);
        exit(2);
    }

    h->allocated = 0;
    shimerge();
}





static void shimerge() {
    header *curr = (header *)heap.bytes;

    while ((char *)curr < heap.bytes + MEMLENGTH) {
        header *next = next_chunk(curr);

        if ((char *)next < heap.bytes + MEMLENGTH &&
            !curr->allocated && !next->allocated) {

            curr->size += next->size;
        } else {
            curr = next;
        }
    }
}





static void leak_detector() {
    header *curr = (header *)heap.bytes;
    size_t bytes = 0;
    int count = 0;

    while ((char *)curr < heap.bytes + MEMLENGTH) {
        if (curr->allocated) {
            bytes += curr->size - sizeof(header);
            count++;
        }
        curr = next_chunk(curr);
    }

    if (count > 0) {
        fprintf(stderr,
                "mymalloc: %zu bytes leaked in %d objects.\n",
                bytes, count);
    }
}