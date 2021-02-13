#include "heapManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


void Insert_Node_to_Heap(heap *t, metadata *tobeInserted);
metadata* Delete_Node_from_Heap(heap *t);
void removeNode(metadata *rem);
void Splay(heap *root, size_t key);