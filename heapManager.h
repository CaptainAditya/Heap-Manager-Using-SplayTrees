#include <stdio.h>
#include <stdlib.h>
#include "chunk.h"

#define MAX_SIZE 1024

#define ALIGNMENT 8

#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))

#define METADATA_SIZE sizeof(metadata)


static heap heapStart = NULL;

metadata* initHeap();
metadata *my_malloc(size_t REQUIRED_SIZE);
void my_free(metadata* toBeFreed);
void *my_realloc(metadata* toBeRealloced, size_t new_size);
metadata* my_calloc(size_t REQUIRED_SIZE);
