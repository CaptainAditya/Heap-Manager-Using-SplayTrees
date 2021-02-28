#include <stdio.h>
#include <unistd.h>
#include "heapManager.h"
#include "heapapi.h"


heap *todebug = &heapStart;

metadata* initHeap(){
    

    size_t max_size = ALIGN(MAX_SIZE);
    
    heapStart = (metadata*)HeapAlloc(GetProcessHeap(), max_size, max_size);

    if (heapStart == (void*) - 1){
        return 0;
    }
           

    heapStart->left = heapStart->right = NULL;
    heapStart->next = heapStart->prev = NULL;
    heapStart->key = max_size - METADATA_SIZE;

    return heapStart;
}


metadata *split (metadata *curr, int numbytes){
  size_t size = METADATA_SIZE + numbytes;
  /*
   size less the metadata cannot be allocated
   */
  if((curr->key - size) <= METADATA_SIZE){
    return curr; 
  }

  metadata* header1 = curr; 
  size_t oldsize = curr->key; 
  curr = curr + 1; 

  char *ptr = (char*) curr; 
  ptr = ptr + numbytes; 

  curr = (metadata*)ptr; 

  metadata* header2 = curr; 
  header2->prev = header2->next = NULL;
  header2->left = header2->right = NULL;
  header2->key = oldsize - (numbytes + METADATA_SIZE); 
  header1->key = oldsize - header2->key; 

  Insert_Node_to_Heap(&heapStart, header2);
  return header1; 

}

metadata *my_malloc(size_t requiredSIZE){
    
    requiredSIZE = ALIGN(requiredSIZE);
    if (heapStart == NULL )
        if (!initHeap())
            return NULL;
    metadata *tobeReturned;
    
    Splay(&heapStart, requiredSIZE);
  
    size_t total_memeory = requiredSIZE + METADATA_SIZE;
    
    metadata *required_Node = Delete_Node_from_Heap(&heapStart);
    if (required_Node -> key == total_memeory){
        return (void*)required_Node + 1;
    }

    else if (required_Node -> key > total_memeory){
      tobeReturned = split(required_Node, requiredSIZE);
      return (void*)(tobeReturned + 1);      
    }

    else{
      //memeory out of range
      //more heap memeory required.
    }
    
    return ;
}
