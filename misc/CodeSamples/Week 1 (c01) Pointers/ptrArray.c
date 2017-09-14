/* 
 * Converting a string to uppercase using a 
 * non-constant pointer to non-constant data.
 */
#include <stdio.h>
#include <ctype.h>

void convertToUppercase(char *sPtr); // prototype

int main(void)
{
   char string[] = "cHaRaCters and $32.98"; // initialize char array

   printf("String before conversion is: %s", string);
   convertToUppercase(string);
   printf("\nString after conversion is: %s\n", string); 
} 

// convert string to uppercase letters
void convertToUppercase(char *sPtr)
{
   while (*sPtr != '\0')  // current character is not '\0' 
     {
       *sPtr = toupper(*sPtr); // convert to uppercase
       ++sPtr; // make sPtr point to the next character
     } 
}
