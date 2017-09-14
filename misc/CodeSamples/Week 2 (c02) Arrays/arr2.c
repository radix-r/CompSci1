/*
 * Michael McAlpin - COP3502 - Spring 2017 
 * Program Name: arr2.c
 * 
 * Objective:
 *  Declare an array of size n as configured by
 *  the command line. 
 *
 * Advantage: Simple
 * Disadvantage: Not very flexible
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Needed for the time()

#define MAX_RAND_VAL 50

int main(int argc, char **argv)
{
  //declare the variables
  int i;
  int x; // because we always need an x ;-)
  int n; // from the CLI!
      
  srand(time(NULL)); // now seed the RNG

  if ( argv[1] > 0)
    n = atoi( argv[1]);
  else
    {
      printf("Expected array size as first parameter\n");
      exit (1);
    }
  printf("Generating %2d random numbers in an array\n", n);
  // Now create the buffer of array size = n INTS
  int *array = malloc(sizeof(int) * n);

  //populate the array with random numbers from ...
  
  for (i = 0; i < n; i++)
       	array[i] = rand() % MAX_RAND_VAL + 1;

  //print the contents of the array
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
