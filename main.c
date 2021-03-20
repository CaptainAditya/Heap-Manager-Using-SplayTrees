#include <stdio.h>
#include <stdlib.h>
#include "heapManager.h"

heap *todebug;

int main(){   
     
     int *a = (int*)my_malloc(sizeof(int)*4);
     a[0] = 0;
     a[1] = 1;
     a[2] = 2;
     a[3] = 3;
     traverse(todebug);
     printf("\n");

     for (int i = 0; i < 4; i++){
          a[i] = i;
          printf("%d ", a[i]);
     }
     
     a = (int*)my_realloc(a, sizeof(int)*2);
     for (int i = 0; i < 8; i++){          
          printf("%d ", a[i]);
     }
     traverse(todebug);

}