/**
 * Implement mergesort algorithm 
 */

#include <stdlib.h>
#include <stdio.h>

int * mergeSort(int *, int);
int * merge(int * , int, int *, int, int *, int);

int main() {
  int testArray[10] = {10, 5, 9, 2, 0, 6, 7, 4, 8, 3};
  int * result;
  int i;
  for (i = 0; i < 10; i++) printf("%d ", testArray[i]);
  printf("\n");
  result = mergeSort(testArray, 10);
  for (i = 0; i < 10; i++) {
    printf("%d ", result[i]);
  }
  printf("\n");
}

int * mergeSort(int * array, int len) {
  int i = 0;
  if (len > 1) {
    int * b = (int *) malloc(sizeof(int) * (len / 2));
    int * c = (int *) malloc(sizeof(int) * ((len / 2) + 1));
    int countB = 0;
    int countC = 0;
    for (i = 0; i < (len / 2); i++) {
      b[i] = array[i];
      countB += 1;
    }
    for (i = len / 2; i < len; i++) {
      c[i - (len / 2)] = array[i];
      countC += 1;
    }
    
    b = mergeSort(b, countB);
    c = mergeSort(c, countC);
    for (i = 0; i < len/2; i++)
      printf("b[%d] = %d;", i, b[i]);
    printf("\n");

    for (i = 0; i < len/2; i++)
      printf("c[%d] = %d;", i, c[i]);
    printf("\n");
    
    array = merge(b, countB, c, countC, array, len);
    free(b);
    free(c);
  }
  return array;
}

/**
 * Merge two sorted array into one array
 * Input: b, c, a array. countB, countC, len is length of the three arrays
 * Ouput sorted array
 */

int * merge(int * b, int countB, int * c, int countC, int * array, int length) {
    int i = 0, j = 0, k = 0, l = 0;
  while (i <  countB && j < countC) {
    if (b[i] <= c[j]) {
	array[k] = b[i];
	i = i + 1;
    } else {
	array[k] = c[j];
	j = j + 1;
    }
    k = k + 1;
    if (i == countB) {
      for (l = 0; l < countC - j ; l++) {
	array[k + l] = c[j + l];
      }
    } else {
      for (l = 0; l < countB - i; l++) {
	array[k + l] = b[i + l];
      }
    }
  }
  return array;
}
