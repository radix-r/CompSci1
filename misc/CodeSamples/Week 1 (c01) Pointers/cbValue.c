/*
 * Cube a variable using pass-by-value.
 */

#include <stdio.h>

int cubeByValue(int n); // prototype

int main(void)
{
   int number = 5; // initialize number

   printf("The original value of number is %d", number);
   
   // pass number by value to cubeByValue
   number = cubeByValue(number);

   printf("\nThe new value of number is %d\n", number);
} 

// calculate and return cube of integer argument                 
int cubeByValue(int n)                                            
{                                                                   
   return n * n * n; // cube local variable n and return result
}
                            
