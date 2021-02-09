#include <stdio.h>
#include <unistd.h>
#include "heapManager.h"

static HEAP_HEADER heapStart = NULL;


void initHeap(){
    heapStart = (metadata*)sbrk(MAX_SIZE);
    heap->left = heapStart->right = NULL;
    heapStart->prev = heapStart->next = NULL;
    return ;
}

