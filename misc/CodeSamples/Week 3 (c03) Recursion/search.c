// Sean Szumlanski
// COP 3502, Summer 2016

// search.c
// ========
// We examined two ways of searching a sorted list for a key and discussed the
// runtime efficiency of each approach. Could you code up a binary search
// function on your own?


#include <stdio.h>
#include <stdlib.h>

#define MAX_RAND_VAL 50

// Linear search. Returns 1 if the key is found in the array, 0 otherwise.
//
// Worst-case: O(n)  (linear time)
// Best-case:  O(1)  (constant time)
//
int linear_search(int *array, int n, int key)
{
	int i;
	
	for (i = 0; i < n; i++)
		if (array[i] == key)
			return 1;
	
	return 0;
}

// Binary search. Returns 1 if the key is found in the array, 0 otherwise.
//
// Worst-case: O(log n)
// Best-case:  O(1)
//
int binary_search(int *array, int n, int key)
{
	int lo = 0, hi = n - 1, mid;
	
	while (lo <= hi)
	{
		// Why use this instead of mid = (hi + lo) / 2, even though they're
		// algebraically equivalent?
		mid = lo + (hi  - lo) / 2;
		
		// If the key is less than the value at mid, consider only the left half
		// of the array.
		if (key < array[mid])
			hi = mid - 1;
		
		// If the key is greater than the value at mid, consider only the right
		// half of the array.
		else if (key > array[mid])
			lo = mid + 1;
		
		// Otherwise, we found the key! Hooray!
		else
			return 1;
	}

	return 0;
}

// Random(ish) bonus knowledge:
//
// This allows me to sort using the qsort() function in C. It returns a
// positive integer if (*a > *b), a negative integer if (*a < *b), and zero if
// (*a == *b). If you want to know more, google "c qsort" and read up on it.
int my_compare(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

// Create and return a sorted array of n random integers.
int *create_sorted_array(int n)
{
	int i, *array = malloc(sizeof(int) * n);

	for (i = 0; i < n; i++)
		array[i] = rand() % MAX_RAND_VAL + 1;

	// Sort the arrays using C's QuickSort function. (See search.c for details.)
	qsort(array, n, sizeof(int), my_compare);

	return array;
}

// Print the contents of an integer array.
void print_array(int *array, int n)
{
	int i;

	if (n == 0)
	{
		printf("(empty)\n\n");
		return;
	}

	for (i = 0; i < n; i++)
		printf("%d ", array[i]);

	printf("\n\n");
}

int main(void)
{
	int *array, n, i;

	printf("How many integers shall we generate? ");
	scanf("%d", &n);

	srand(time(NULL));

	// Create and print sorted array of random integers.
	array = create_sorted_array(n);

	printf("array:\n");
	print_array(array, n);

	// Test our search algorithms. Recall from class that this isn't a great
	// approach, because it will almost always only search for things in the
	// first half of the array. That doesn't give us a complete view of whether
	// our binary search function is working correctly. How can we test more
	// thoroughly?
	printf("Linear Search:\n");
	printf("==============\n");
	for (i = 0; i <= 10; i++)
	{
		printf("Searching for %d... ", i);

		if (linear_search(array, n, i))
			printf("FOUND KEY!\n");
		else
			printf("not found.\n");
	}

	printf("\nBinary Search:\n");
	printf("==============\n");
	for (i = 0; i <= 10; i++)
	{
		printf("Searching for %d... ", i);

		if (binary_search(array, n, i))
			printf("FOUND KEY!\n");
		else
			printf("not found.\n");
	}

	// Clean up after yourself.
	free(array);
	
	return 0;
}
