/* 
 * C Program to Sort an Integer Array using Radix Sort Algorithm
 */

#include <stdio.h>

int min = 0, count = 0, array[100] = {0}, array1[100] = {0};

int main()
{
 int k, i, j, temp, t, n;

 printf("Enter size of array :");
 scanf("%d", &count);

 printf("Enter elements into array :");
 for (i = 0; i < count; i++)
 {
     scanf("%d", &array[i]);
     array1[i] = array[i];
 }

 for (k = 0; k < 4; k++)
 {
   /*
     NB There is a discrepancy with any number ending in 0
        and it will be sorted in NEXT MSD order NOT
        based on LSD... zztop
    */
     for (i = 0; i < count; i++)
     {
         min = array[i] % 10;        /* To find minimum lsd */
         t = i;
         for (j = i + 1; j < count; j++)    
         {
             if (min > (array[j] % 10))
             {
                 min = array[j] % 10; 
                 t = j;
             }
         }
         temp = array1[t];
	 printf("temp.%d:%d; ", k, temp);
         array1[t] = array1[i];
	 printf("array1.%d:%d;\n ", k, array1[i]);
         array1[i] = temp;

	 temp = array[t];
         array[t] = array[i];
         array[i] = temp;
     }

     for (j = 0; j < count; j++)        /*to find MSB */
         array[j] = array[j] / 10;

 }

 printf("Sorted Array (radix sort) : ");
 for (i = 0; i < count; i++)
     printf("%d ", array1[i]);
 printf("\n");
}
