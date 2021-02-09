#include <stdio.h>
#include "heapManager.h"
#include "heapapi.h"


static heap heapStart = NULL;

int initHeap(){

    size_t max_size = ALIGN(MAX_SIZE);
    
    heapStart = (metadata*)HeapAlloc(GetProcessHeap(), 0, max_size);

    if (heapStart == (void*) - 1){
        return 0;
    }
    heapStart->left = heapStart->right = NULL;
    heapStart->prev = heapStart->next = NULL;

    heapStart->key = max_size - METADATA_SIZE;
    printf("%d", heapStart->key);
    return 1;
}


metadata *my_malloc(size_t requiredSIZE){
    
    requiredSIZE = ALIGN(requiredSIZE);
    if (heapStart == NULL )
        if (! initHeap())
            return NULL;
    
    


    

}

