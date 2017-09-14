#include <stdio.h>
#include <stdlib.h>
 
long fib(int);

int main(int argc, char **argv)
{
  //declare the variables

  int n; // from the CLI
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
  
  f = fib(n);
  printf("F(%d) = %ld\n", n, f);
  return 0;
}
 
long fib(int n)
{
  // printf("in %d; ", n);
  //base cases: F(0) = 0, F(1) = 1
  if (n < 2)
     return n;
  //definition of Fibonacci: F(n) = F(n - 1) + F(n - 2)
  return fib(n - 1) + fib(n - 2);
}
