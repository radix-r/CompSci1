/* 
* C Program for counting sort 
*/

#include <stdio.h>  

/*  Counting sort function  */ 
void counting_sort(int A[], int k, int n) 
{
int i, j;
int B[15], C[100];
//Initialize scratch array
for (i = 0; i <= k; i++)
  C[i] = 0;
 
for (j = 1; j <= n; j++)
  {
    C[A[j]] = C[A[j]] + 1;
    printf("A[j]: %d;", A[j]);
  }
 printf("\n");
 //Count of counts
for (i = 1; i <= k; i++)
  {
    C[i] = C[i] + C[i-1];
    printf("C[%d] = %d;", i, C[i]);
  }
printf("\n");
//Now build the sorted array
for (j = n; j >= 1; j--) 
{
  B[C[A[j]]] = A[j];
  C[A[j]] = C[A[j]] - 1;
  printf("2A[%d]: %d;",j , A[j]);
}
 printf("\n");

printf("The Sorted array is : ");
for (i = 1; i <= n; i++)
  printf("%d ", B[i]);
printf("\n");
}

/*  End of counting_sort()  */

/*  The main() begins  */

int main()
{
  int n, k = 0, A[15], i;
  printf("Enter the number of input : ");
  scanf("%d", &n);
  printf("\nEnter the elements to be sorted :\n");

  for (i = 1; i <= n; i++) 
    {
      scanf("%d", &A[i]);
      if (A[i] > k) {
	k = A[i];
      }
    }

  counting_sort(A, k, n); 
  printf("\n");

  return 0;

}
