/*
 * C Program to find whether a Number is Prime or Not using Recursion
 */

#include <stdio.h>

int primeno(int, int);
int main()
{
    int num, check;
    //collect a number from the user..
    printf("Enter a number: ");
    scanf("%d", &num);

    //check to see if the number is prime
    check = primeno(num, num / 2);

    //A return value of 1 indicates prime-ness.
    if (check == 1)
    {
        printf("%d is a prime number\n", num);
    }
    else //or not prime-ness
    {
        printf("%d is not a prime number\n", num);
    }

    return 0;
}

/*
 * Recursive algorithms must have:
 * [1] Base case - well-defined terminating condition(s)
 *     (in other languages aka a "guard condition")
 * [2] Some process or steps to resolve to the base case
 * [3] Call to self to test & process again, (& again...)
 *     (voila! we have recursion) 
 */ 

int primeno(int num, int i)
{
  // [1] Base case
  // The remainder is 1 and we're done
  // looking for a prime!
  // NB a prime is divisible by iteself & 1
  if (i == 1)
    {
        return 1;
    }
    else
    {
      //[2] The process to resolve towards the base case
      // Is there a factor?
      if (num % i == 0) //YES - not prime
       {
         return 0;
       }
      else
	// Try again...
       {
	// [3] - Call to self...
         return primeno(num, i - 1);
       }       
    }
}
