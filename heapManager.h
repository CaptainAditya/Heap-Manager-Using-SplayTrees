#include <stdio.h>
#include <stdlib.h>
#include "chunk.h"
#include <stddef.h>
#define MAX_SIZE 1024

#define ALIGNMENT 8

#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))

#define METADATA_SIZE sizeof(metadata)
#define MAX_SIZE 1024

int initHeap();
metadata *my_malloc(size_t REQUIRED_SIZE);
void my_free(metadata* toBeFreed);
metadata* my_realloc(metadata* toBeRealloced, size_t Excess);
metadata* my_calloc(size_t REQUIRED_SIZE);
