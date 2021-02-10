#include <stdio.h>
#include <unistd.h>
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

    heapStart->key = max_size - METADATA_SIZE;
    return ;
}
metadata *split (metadata *curr, int numbytes){
  size_t size = sizeof(metadata_t) + numbytes;
  /*If the current block's size minus the size needed is less than the size of metadata, return the pointer. 
    This prevents a split that would result in a block that is smaller than a metadata, which could never be
    allocated. */
  if((curr->size - size) <= sizeof(metadata)){
    return curr; 
  }
  metadata* header1 = curr; //Initializing header for new block to be returned
  size_t oldsize = curr->size; 
  curr = curr + 1; //Move pointer past the header 
  char *ptr = (char*) curr; 
  ptr = ptr + numbytes; 

  curr = (metadata*)ptr; //Restore pointer to metadata type
  /*Initialize new free block and block to be returned*/
  metadata* header2 = curr; //Create header for leftover block
  header2->size = oldsize - (numbytes + sizeof(metadata_t)); 
  header1->size = oldsize - header2->size; 
  
  Insert_into_Heap(&heapStart, header2);

  return header1; 

}

metadata *my_malloc(size_t requiredSIZE){
    
    requiredSIZE = ALIGN(requiredSIZE);
    if (heapStart == NULL )
        if (! initHeap())
            return NULL;
    
    Splay(&heapStart, requiredSIZE);

    /*
    idhar aayega kuch
    */
    size_t total_memeory = requiredSIZE + METADATA_SIZE;
    
    metadata *required_Node = Delete_Node_from_Heap(&heapStart);

    if (required_Node -> key == total_memory){
        return (void*)required_node + 1;
    }

    else if (required_Node -> key > total_memeory){

        size_t rem = total_memeory - requiredSIZE;
        return (void*)split(required_Node, requiredSIZE) + 1;
        
    }

    return ;
}
