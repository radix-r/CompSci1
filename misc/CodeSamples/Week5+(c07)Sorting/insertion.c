/*
 * C Program to Implement Insertion Sort
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

#define MAX 7

void insertion_sort(int *);

int main()
{
  int a[MAX], i;
  
  printf("enter elements to be sorted:");

  for (i = 0;i < MAX;i++)
  {
    scanf("%d", &a[i]);
  }

  insertion_sort(a);

  printf("sorted elements:\n\n");

  for (i = 0;i < MAX; i++)
    {
      printf(" %d", a[i]);

     }
  printf("\n");

}


/* sorts the input */

void insertion_sort(int * x)
{
  int temp, i, j;

  for (i = 1;i < MAX; i++)
    {
      temp = x[i];
      j = i - 1;

      while (temp < x[j] && j >= 0)
	{
	  x[j + 1] = x[j];
	  j = j - 1;
	}
       x[j + 1] = temp;

    }

}
