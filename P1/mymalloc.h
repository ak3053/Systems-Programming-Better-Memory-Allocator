#ifndef MYMALLOC_H
#define MYMALLOC_H



#include <stdlib.h>
#define malloc(X) mymalloc (X, __FILE__, __LINE__)
#define free(X) myfree (X, __FILE__, __LINE__)

void * mymalloc(size_t, char *, int);
void myfree(void *, char *, int);

#endif
