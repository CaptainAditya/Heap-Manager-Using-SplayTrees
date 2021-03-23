#include <stdio.h>
#include <stdlib.h>
#include "heapManager.h"

heap *todebug;

typedef struct info{
     int roll;
     char *a;
}info;


int main(){   
     
    info* a = (info*)my_malloc(sizeof(info));
    a->roll = 2;
    a->a = (char*)my_malloc(sizeof(char)*20);
    strcpy(a->a, "Hello");
    printf("%d %s", a->roll, a->a);
    printf("\n");
    traverse(todebug);
    my_free(a->a);
    printf("\n");
    traverse(todebug);
    my_free(a);
    printf("\n");
    traverse(todebug);


   
}