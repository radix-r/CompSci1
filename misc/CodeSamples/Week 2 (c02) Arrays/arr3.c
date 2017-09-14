/*
 * Michael McAlpin - COP3502 - Spring 2017
 * Program Name: arr3.c
 * 
 * Objective:
 *  Declare an array of size n as configured by
 *  the user. Then create the buffer for the array,
 *  AND initialize it with random(ish) integers... 
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
      
  //srand(time(NULL)); // now seed the RNG

  if ( argv[1] > 0)
    n = atoi( argv[1]);
  else
    {
      printf("Expected array size as first parameter\n");
      exit (1);
    }
  printf("Generating %2d random numbers in an array\n", n);

  // Now create the buffer of array size = n INTS
  int *array = create_array(n);

  //print the contents of the array

  printf("array:\n");
  print_array(array, n);
	
}
