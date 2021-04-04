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
        return (void*)(required_Node + 1);
    }

    else if (required_Node -> key > total_memeory){
      tobeReturned = split(required_Node, requiredSIZE);
      
      return (void*)(tobeReturned + 1);      
    }

    else{
      Insert_Node_to_Heap(&heapStart, required_Node);
      Splay(&heapStart, total_memeory);
      required_Node = Delete_Node_from_Heap(&heapStart);
      if (required_Node->key == total_memeory)
        return (void*)(required_Node + 1);
      else if (required_Node->key > total_memeory){
        tobeReturned = split(required_Node, requiredSIZE);
        return (void*)(tobeReturned + 1);
      }
      
    }
    
    return NULL;
}

void my_free(metadata* tobefreed){

    tobefreed -=  1;
    
    char *curr = (char*)tobefreed;

    int i = 0;

    curr += METADATA_SIZE;

    while (i < tobefreed->key  - METADATA_SIZE){
      *curr = NULL;
      curr++;
      i++;
    }        

    Insert_Node_to_Heap(&heapStart, tobefreed);
}



metadata *my_calloc(size_t requiredSize){
  
  metadata *tobereturned = (metadata*)my_malloc(requiredSize);
  int toEnd = ALIGN(requiredSize) / 4;
  int i = 0;
  int *traversal = (int*)tobereturned;
  while (i < toEnd){
    *traversal = 0;
    traversal += 1;
    i++;
  }     
  return tobereturned;
}

void* my_realloc(metadata *tobeRealloced, size_t size){
  size = ALIGN(size);
  metadata* tobeAdded;
  tobeRealloced -= 1;
  
  if (tobeRealloced->key - METADATA_SIZE < size){
    
    //create new block
    tobeAdded = (metadata*)my_malloc(size);   
    //copy content 
    
      
    char *new = (char*)(tobeAdded);
    char *prev = (char*)(tobeRealloced + 1);
    
    for (int i = 0; i < tobeRealloced->key - METADATA_SIZE; i++){
      *(new + i) = *(prev + i);
    }  
          
    //free previous pointer
    tobeRealloced += 1;
    my_free(tobeRealloced);
    return (void*)(tobeAdded);
  }

  else if (tobeRealloced->key - METADATA_SIZE > size){
    
    char *curr = (char*)tobeRealloced;
    curr += size;
    for (int i = size; i < tobeRealloced->key - METADATA_SIZE; i++){
      *curr = NULL;
      curr++;
    }
    //use split
    tobeRealloced = split(tobeRealloced, size);
    //copy content
    return (void*)(tobeRealloced + 1);        
    //return
  }  
  else
    return tobeRealloced;
}

void traverse(heap *t){
    if (!*t)
      return ;
    traverse(&((*t)->left));
    
    if ((*t)->next){
      printf("(");
      metadata *p = *t;
      while (p->next) { 
        printf("%zu ", (*t)->key);
        p = p->next;
      }
      printf(") ");
    }

    else
      printf("%zu ", (*t)->key);
    traverse(&((*t)->right));
    return ;
    
}