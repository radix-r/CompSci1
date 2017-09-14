#include <stdio.h>
#include <stdlib.h>
 
long factorial(int);

int main(int argc, char **argv)
{
  //declare the variables

  int n; // from the CLI!
  long f;
  
  if ( argv[1] > 0)
    {
      n = atoi( argv[1]);
      if (n < 0)
	{
	  printf("Negative integers are not allowed.\n");
	  exit (1);
	}
    }
  else
    {
      printf("Expected a positive integer for first parameter.\n");
    }
  
  f = factorial(n);
  printf("%d! = %ld\n", n, f);
  

   
  return 0;
}
 
long factorial(int n)
{
  if (n == 0)
    return 1;
  else
    return(n * factorial(n-1));
}
