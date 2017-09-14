/*
 * Michael McAlpin - COP3502 - Spring 2017
 * Program Name: arr1.c
 * 
 * Objective:
 *  Declare an array of size n as configured by
 *  the programmer. 
 *
 * Advantage: Simple
 * Disadvantage: Not very flexible
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Needed for the time()

#define MAX_RAND_VAL 50

int main()
{
  //declare the variables
  int i;
  int x; // because we always need an x ;-)
  int n = 50; // hard coded - should it be
              // initialized from the CLI?
  int array[50];
    
  srand(time(NULL)); // now seed the RNG
  
  //Populate the array with random numbers from ...
  
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

}
