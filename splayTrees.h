#include "heapManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void removeNode(metadata *rem);
void Splay(heap *root, size_t key);