#include <stdio.h>
#include <stdlib.h>
#include "chunk.h"

#define MAX_SIZE 1024

void initHeap(HEAP_HEADER *p);
metadata *my_malloc(size_t REQUIRED_SIZE);
void my_free(matadata* toBeFreed);
void my_realloc(metadata* toBeRealloced, size_t Excess);
void my_calloc(size_t REQUIRED_SIZE);


