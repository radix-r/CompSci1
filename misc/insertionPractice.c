/*
This is a implementation of insertion sort I am writing to study for exam 2
*/

/*
 * Challenge  objectives:
 * 1. Read input from stdin until last digit = 0. (O)
 * 2. Change the arrays to pointers.
 * 3. Sort plaintext alphabetically.
 *    a. Input from stdin until EOF
 * 4. Sort in reverse order
 */
 
 #include <stdio.h>
 
 #define MAX 7
 
 void insertion_sort(int *, int);
 
 int main()
 {
 	int a[MAX], i, n=0, input;
 	
 	printf("Enter integers to sort or 0 to continue\n");
 	do
	{
 		scanf("%d", &input);
 		
 		if (input !=0)
 		{
 			a[n] = input;
 			n++;
		}
		
	}while(input != 0 && n < MAX);
	
	
	insertion_sort(a, n);
	
	printf("Sorted elements: \n\n");
	
	for(i = 0; i< n; i++)
	{
		printf(" %d", a[i]);
	}
	printf("\n");
	
	return 0;
 }
 
 
 /*
 Sorts the inputed int array 
 */
 void insertion_sort(int * x, int size)
 {
 	int temp, i, j;
 	
 	for(i =1; i < size; i++)
 	{
 		temp = x[i];
 		j = i-1;
 		
 		while(temp < x[j] && j >=0)
 		{
 			x[j+1] = x[j];
 			j = j-1;
		}
		
		x[j+1] = temp;
	}
	 
 }
 
 
