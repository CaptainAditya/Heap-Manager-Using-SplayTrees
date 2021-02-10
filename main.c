#include <stdio.h>
#include <stdlib.h>
#include "heapManager.h"

int main(){
    heap t;
    init(&t);
    insert(&t, 20);
    insert(&t, 13);
    insert(&t, 25);
    insert(&t, 10);
    insert(&t, 16);
    insert(&t, 40);
    insert(&t, 22);
    print2D(t);
    Delete_Node_from_Heap(&t);
    printf("-----------------------\n");
    print2D(t);
}