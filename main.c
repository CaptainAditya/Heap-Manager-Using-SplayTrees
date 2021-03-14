#include <stdio.h>
#include <stdlib.h>
#include "heapManager.h"

heap *todebug;

int main(){   
     int *a = (int*)my_calloc(sizeof(int)*4);
     

     for (int i = 0; i < 4; i++)printf("%d ", a[i])  ;

     my_free(a);

     
     for (int i = 0; i < 4; i++)printf("%d ", a[i])  ;

}