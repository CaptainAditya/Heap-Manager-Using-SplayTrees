#include <stdio.h>
#include <stdlib.h>
#include "chunk.h"

heap *todebug;

int main(int argc, char *argv[])
{
    // Summary of Calls
    // A. ar0 = my_malloc(5)
    // B. ar1 = my_malloc(200)
    // C. ar2 = my_malloc(900) **Supposed to fail**

    char *ar0, *ar1, *ar2, *ar3, *ar4, *ar5, *ar6;
    int i;

    // my_malloc Ar0
    printf("ar 0: calling my_malloc(5)\n");
    ar0 = my_malloc(5);
    if (ar0 == NULL) {
        fprintf(stderr, "ar0 my_malloc has failed");
        exit(1);
    } 
    
    for (i = 0; i < 5; ++i) {
        ar0[i] = 'B';
    }

    for (i = 0; i < 5; ++i) {
        printf("%c", ar0[i]);
    }
    printf("\n");


    // my_malloc Ar1
    printf("ar 1: calling my_malloc(5)\n");
    ar1 = my_malloc(5);
    if (ar1 == NULL) {
        fprintf(stderr, "ar1 my_malloc has failed");
        exit(1);
    } 
    
    for (i = 0; i < 5; ++i) {
        ar1[i] = 'C';
    }

    for (i = 0; i < 5; ++i) {
        printf("%c", ar1[i]);
    }
    printf("\n");

    // my_malloc Ar2
    printf("ar 2: calling my_malloc(5)\n");
    ar2 = my_malloc(5);
    if (ar2 == NULL) {
        fprintf(stderr, "ar2 my_malloc has failed");
        exit(1);
    } 
    
    for (i = 0; i < 5; ++i) {
        ar2[i] = 'D';
    }

    for (i = 0; i < 5; ++i) {
        printf("%c", ar2[i]);
    }
    printf("\n");

    // my_malloc Ar3
    printf("ar 3: calling my_malloc(5)\n");
    ar3 = my_malloc(5);
    if (ar3 == NULL) {
        fprintf(stderr, "ar3 my_malloc has failed");
        exit(1);
    } 
    
    for (i = 0; i < 5; ++i) {
        ar3[i] = 'E';
    }

    for (i = 0; i < 5; ++i) {
        printf("%c", ar3[i]);
    }
    printf("\n");

    // my_malloc Ar4
    printf("ar 4: calling my_malloc(5)\n");
    ar4 = my_malloc(5);
    if (ar4 == NULL) {
        fprintf(stderr, "ar4 my_malloc has failed");
        exit(1);
    } 
    
    for (i = 0; i < 5; ++i) {
        ar4[i] = 'F';
    }

    for (i = 0; i < 5; ++i) {
        printf("%c", ar4[i]);
    }
    printf("\n");

    printf("calling my_free(ar1)\n");
    my_free(ar1);
    printf("calling my_free(ar4)\n");
    my_free(ar4);
    printf("calling my_free(ar0)\n");
    my_free(ar0);
    printf("calling my_free(ar2)\n");
    my_free(ar2);
     traverse(todebug);
    // my_malloc Ar5
    printf("ar 5: calling my_malloc(12)\n");
    ar5 = my_malloc(12);
    
    if (ar5 == NULL) {
        fprintf(stderr, "ar5 my_malloc has failed");
        exit(1);
    } 
    
    for (i = 0; i < 12; ++i) {
        ar5[i] = 'G';
    }
    for (i = 0; i < 12; ++i) {
        printf("%c", ar5[i]);
    }
    printf("\n");

    printf("calling my_free(ar3)\n");
    my_free(ar3);


    printf("ALL GENERAL TESTS PASSED\n");
}