#include <stdio.h>

typedef struct metadata{
    size_t key;
    struct node *left, *right;
    struct node *prev, *next;
}metadata;

typedef metadata* HEAP_HEADER;
