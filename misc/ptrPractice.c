/*
pointer practice
*/

#include <stdio.h>

void swap(int* a, int* b);

int main(void)
{
	int x = 10;
	int v = 5;
	
	swap(&x,&v);
	
	printf("x = %d \nv = %d", x,v); 
	return 0;
}

void swap(int* a, int* b)
{
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}
