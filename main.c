#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chunk.h"

heap *todebug;


int main(){

	
	
	int size;
	int *ptr[10];
	int i;
	system("cls");
	printf("We have array of pointers of size 10\n\n");

	/*
 	 * try mallocing four pieces, each 1/4 of total size
 	 */
	printf("Initially Free Block: %zu\n\n", MAX_SIZE);
	
	size = MAX_SIZE/ 4;

	ptr[0] = (int*)my_malloc(size);
	if(ptr[0] == NULL)	{
		printf("malloc of ptr[0] failed for size %d\n\n", size);
		exit(1);
	}

	printf("After malloc of %zu to ptr[0]: ", size);
	getch();
	traverse(todebug);
	printf("\n\n");
	
	ptr[1] = (int*)my_malloc(size);
	if(ptr[1] == NULL)	{
		printf("malloc of ptr[1] failed for size %d\n\n", size);
		exit(1);
	}
	printf("After malloc of %zu on ptr[1]: ", size);
	getch();
	traverse(todebug);
	printf("\n\n");

	ptr[2] = (int*)my_malloc(size);
	if(ptr[2] == NULL)	{
		printf("malloc of ptr[2] failed for size %d\n\n", size);
		exit(1);
	}
		
	printf("After malloc of %zu on ptr[2]: ", size);
	getch();
	traverse(todebug);
	printf("\n\n");

	/*
  	 * this one should fail due to rounding
  	 */

	printf("After malloc of %zu on ptr[3]: ", size);

	ptr[3] = (int*)my_malloc(size);
	
	traverse(todebug);
	if(ptr[3] == NULL){

		printf("\n\nmalloc of ptr[3] fails correctly for size %d\n\n", size);
		
	}
	printf("\n\nFreeing ptr[0] of %zu :", size);
	getch();
	/*
  	 * free the first block
  	 */
	my_free(ptr[0]);
	traverse(todebug);
	printf("\n\n");
	/*
  	 * free the third block
   	 */
	printf("Freeing ptr[2] of %zu :", size);
	my_free(ptr[2]);
	getch();
	traverse(todebug);
	printf("\n\n");
	/*
  	 * now free secoond block
   	 */
	printf("Freeing ptr[1] of %zu :", size);

	my_free(ptr[1]);
	getch();
	traverse(todebug);
	printf("\n\n");
	/*
 	 * re-malloc first pointer
  	 */
	ptr[0] = (int*)my_malloc(size);
	printf("Again malloc to ptr[0] of %zu: ", size);
	if(ptr[0] == NULL)
	{
		printf("re-malloc of ptr[0] failed for size %d\n\n", size);
		exit(1);
	}
	getch();
	traverse(todebug);
	printf("\n\n");
	/*
  	 * try splitting the second block
  	 */
	ptr[1] = (int*)my_malloc(size/2);
	printf("Now allocating %zu to ptr[1] : ", size / 2);
	if(ptr[1] == NULL)
	{
		printf("split second block ptr[1] failed for size %d\n\n", size/2);
		exit(1);
	}
	getch();
	traverse(todebug);
	printf("\n\n");	

	/*
  	 * free first block and split of second
 	 */
	printf("Freeing ptr[0] which has size %zu : ", size);
	my_free(ptr[0]);
	getch();
	traverse(todebug);
	printf("\n\n");

	printf("Freeing ptr[1] which has size %zu : ", size / 2);
	my_free(ptr[1]);
	getch();
	traverse(todebug);
	printf("\n\n");


	/*
 	 * To check if multiples word
  	 */
	for(i=0; i < 6; i++){
		printf("Allocating 100 bytes to ptr[%d] : ", i);
		ptr[i] = my_malloc(100);
		getch();
		traverse(todebug);
		printf("\n\n");
	}
	/*
 	 * free first block, third block, fifth block
  	 */
	printf("Freeing ptr[0] of size 100 : ");
	getch();
	my_free(ptr[0]);
	traverse(todebug);

	printf("\n\nFreeing ptr[2] of size 100 : ");
	getch();
	my_free(ptr[2]);
	traverse(todebug);

	printf("\n\nFreeing ptr[4] of size 100 : ");
	getch();
	my_free(ptr[4]);
	traverse(todebug);

	printf("\n\n");
	/*
 	 * now, free second block -- first, second, third blocks
   	 * should coalesce
	 */
	printf("\n\nFreeing ptr[1] of size 100 : ");
	my_free(ptr[1]);
	getch();
	traverse(todebug);
	printf("\n\n");

	/*
	 * free the sixth block and it shoudl merge with the last
  	 * block leaving two
 	 */
	printf("\n\nFreeing ptr[5] of size 100 : ");
	my_free(ptr[5]);
	getch();
	traverse(todebug);
	printf("\n\n");

	/*
  	 * now free fourth block and they should all be together
  	 */
	printf("\n\nFreeing ptr[3] of size 100 : ");
	my_free(ptr[3]);
	getch();
	traverse(todebug);
	printf("\n\n");

	printf("Stress testcases passed!\n\n");

	return;
}