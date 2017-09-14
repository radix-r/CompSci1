/*
 * Michael McAlpin - COP3502 - Spring 2017
 * Program Name: arr4.c
 * 
 * Objective:
 *  Declare an array of size n as configured by
 *  the user. Then create the buffer for the array,
 *  AND initialize it with random integers... 
 * 
 *  Build a SORTED array in prep for comparison
 *
 *  Search & the big O
 *  Compare two arrays?
 *
 * Advantage: User can configure the size
 * Disadvantage: More flexible
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Needed for the time()

#define MAX_RAND_VAL 50
// Create an array and fill it with random numbers
int *create_array(int n)
{
  int i, *array = malloc(sizeof(int) * n);
  srand(time(NULL)); // now seed the RNG
  for (i = 0; i < n; i++)
    array[i] = rand() % MAX_RAND_VAL + 1;

  return array;
}

// Random(ish) bonus knowledge:
//
// This allows me to sort using the qsort() function in C. It returns a
// positive integer if (*a > *b), a negative integer if (*a < *b), and zero if
// (*a == *b). If you want to know more, google "c qsort" and read up on it.
int my_compare(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

// Create and return a sorted array of n random integers.
int *create_sorted_array(int n)
{
	int i, *array = malloc(sizeof(int) * n);

	for (i = 0; i < n; i++)
		array[i] = rand() % MAX_RAND_VAL + 1;

	// Sort the arrays using C's QuickSort function. (See search.c for details.)
	qsort(array, n, sizeof(int), my_compare);

	return array;
}

// Print the contents of an integer array.
void print_array(int *array, int n)
{
  int i, x;
  //Defense!
  if (n == 0)
    {
      printf("(empty)\n\n");
      return;
    }

  for (i = 0; i < n; i++)
    {
      printf(" [%2d] = %2d ", i, array[i]);
      // now print the array's contents - 5 to line.
      x = i + 1; // we live in a land of zero relative
      if ((x % 5) == 0)
	printf("\n");
    }
  printf("\n");
}

int main(int argc, char **argv)
{
  //declare the variables
  int i;
  int n; // from the CLI!
      
  if ( argv[1] > 0)
    n = atoi( argv[1]);
  else
    {
      printf("Expected array size as first parameter\n");
      exit (1);
    }
  printf("Generating %2d random numbers in an array\n", n);

  // ARRAY #1
  // Now create the buffer of array size = n INTS
  int *array1 = create_array(n);

  //print the contents of the first array

  printf("array1:\n");
  print_array(array1, n);

  // ARRAY #2
  // Now create the buffer of array size = n INTS
  int *array2 = create_sorted_array(n);

  //print the contents of the array

  printf("array2:\n");
  print_array(array2, n);

  // ARRAY #3
  // Now create the buffer of array size = n INTS
  int *array3 = create_sorted_array(n);

  //print the contents of the array

  printf("array3:\n");
  print_array(array3, n);
	
}
