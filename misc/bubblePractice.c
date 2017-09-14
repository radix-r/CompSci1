/*
This is a copy of bubble sort that I am typing up to study for exam 2
*/

/*
 * Challenge  objectives:
 * 1. Read input from stdin until last digit = 0.
 * 2. Change the arrays to pointers.
 * 3. Sort plaintext alphabetically.
 *    a. Input from stdin until EOF
 * 4. Sort in reverse order
 */
 
 #include <stdio.h>
 
 int main()
 {
 	int array[100], n=0, c, d, swap, input;
 	
 	printf("Enter integers to sort or 0 to continue\n");
 	do
	{
 		scanf("%d", &input);
 		
 		if (input !=0)
 		{
 			array[n] = input;
 			n++;
		}
	}while(input != 0 && n < 100);
 	
 	for(c=0; c<(n-1); c++)
 	{
 		for(d = 0; d < n-c-1; d++)
 		{
 			if (array[d] > array[d+1])
 			{
 				swap = array[d];
 				array[d] = array[d+1];
 				array[d+1] = swap;
 				// bubbles larger numbers to higher indexes
			}
		}
	}
	
	printf("Sorted list in ascending order:\n");
	
	for(c = 0; c < n; c++)
	{
		printf(" %d\n", array[c]);
	}
	
	return 0;
	
	
	
 }
