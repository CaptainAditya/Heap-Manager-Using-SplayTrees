#include <stdio.h>
#include <unistd.h>
#include "heapManager.h"
#include "heapapi.h"



int initHeap(){
    

    size_t max_size = ALIGN(MAX_SIZE);
    
    heapStart = (metadata*)HeapAlloc(GetProcessHeap(), 0, max_size);

    if (heapStart == (void*) - 1){
        return 0;
    }
           

    heapStart->left = heapStart->right = NULL;
    heapStart->next = heapStart->prev = NULL;
    heapStart->key = max_size - METADATA_SIZE;
    
    return ;
}
metadata *split (metadata *curr, int numbytes){
  size_t size = METADATA_SIZE + numbytes;
  /*If the current block's size minus the size needed is less than the size of metadata, return the pointer. 
    This prevents a split that would result in a block that is smaller than a metadata, which could never be
    allocated. */
  if((curr->key - size) <= METADATA_SIZE){
    return curr; 
  }
  metadata* header1 = curr; //Initializing header for new block to be returned
  size_t oldsize = curr->key; 
  curr = curr + 1; //Move pointer past the header 
  char *ptr = (char*) curr; 
  ptr = ptr + numbytes; 

  curr = (metadata*)ptr; //Restore pointer to metadata type
  /*Initialize new free block and block to be returned*/
  metadata* header2 = curr; //Create header for leftover block
  header2->key = oldsize - (numbytes + METADATA_SIZE); 
  header1->key = oldsize - header2->key; 

  Insert_Node_to_Heap(&heapStart, header2);

  return header1; 

}

metadata *my_malloc(size_t requiredSIZE){
    
    requiredSIZE = ALIGN(requiredSIZE);
    if (heapStart == NULL )
        if (! initHeap())
            return NULL;
    metadata *tobeReturned;
    Splay(&heapStart, requiredSIZE);
  
    /*
    idhar aayega kuch
    */
    size_t total_memeory = requiredSIZE + METADATA_SIZE;
    
    metadata *required_Node = Delete_Node_from_Heap(&heapStart);
  
    if (required_Node -> key == total_memeory){
        return (void*)required_Node + 1;
    }

    else if (required_Node -> key > total_memeory){
      tobeReturned = split(required_Node, requiredSIZE);
      return (void*)(tobeReturned + 1);      
    }
  
    //realloc
    return ;
}
