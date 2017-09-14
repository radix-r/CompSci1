/*
Malloc practice
*/

#include <stdio.h>
#define SIZE 5

int main(void)
{
	//create int array size 5
	int * array = NULL;
	array = malloc(SIZE * sizeof(int));
	int i;
	
	// ensure that mem was allocated
	if(NULL == array)
	{
		fprintf(stderr,"malloc failed\n");
		return -1;
	}
	
	// fill the array
	for(i = 0; i < SIZE; i++)
	{
		array[i] = i;
	}
	
	// print the array
	for(i = 0; i < SIZE; i++)
	{
		printf("array[%d] = %d\n", i, *(array+i));
	 }
	  
	free(array);
	return 0;
}
