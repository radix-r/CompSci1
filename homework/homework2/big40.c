/*
Ross Wagner Homework 2
NID: ro520462


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "big40.h"

//
int initInteger40(Integer40 **p);

/*
Return a pointer to a new, dynamically allocated Integer40 struct that contains the
result of adding the 40 digit integers represented by p and q.
*/
Integer40 *big40Add(Integer40 *p, Integer40 *q)
{
	// create place to store sum
	Integer40 *sum = NULL;
	// initalize. initInteger40 returns 1 or 0. can be used as a boolean
	int initSucess = initInteger40(&sum);
	
	//Check if inputs are null
	if(p == NULL || q == NULL || !initSucess)
	{
		fprintf(stderr,"big40Add input failure\n");
		return NULL;
	}
	
	// declare index and temp sum
	int i; int tempSum; int carry = 0;
	for(i = 0; i < 40; i++)
	{
		// sum ith digits in p and q
		tempSum = p->digits[i] + q->digits[i] + carry;
		
		//if temp sum is greater than 16 set carry to 1
		if (tempSum >= 0x10)
		{
			carry = 1;
			sum->digits[i] = tempSum%0x10;
		}
		else
		{
			carry = 0;
			sum->digits[i] = tempSum;
		} 
	}
	
	return sum;
	
}

/*
Destroy any and all dynamically allocated memory associated with p. Avoid segmentation
faults and memory leaks.
*/
Integer40 *big40Destroyer(Integer40 *p)
{
	if (p != NULL && p->digits != NULL )
	{
		//bfree field in Integer40
		free(p->digits);
		// free the Integer40 itself
		free(p);
		
	}
	
	return NULL;
}

// find the nth fibonacci number
Integer40 *fibBig40(int n, Integer40 *first, Integer40 *second)
{
	int i;
	
	Integer40 *low = NULL, *high = NULL, *temp = NULL;
	
	low = first;
	high = second; 
	
	for(i = 0; i < n; i++)
	{
		temp = big40Add(low, high);
		low = high;
		high = temp;
	}
	
	return high;
}

/*

*/
void big40Rating(void)
{
	//hour tally: 8
	
	fprintf(stderr,"ro520462;3;8\n");

}

/*
Convert a number from string format to Integer40 format. (For example function
calls, see big40-main01.c.)
*/
Integer40 *parseString(char *str)
{
	
	Integer40 *num = NULL;
	int initSucess = initInteger40(&num);
	if ( !initSucess || str == NULL)
	{
		fprintf(stderr,"parseString failed\n");
		return NULL;
	}
	
	
 
 	// string for strtol
 	char digit[2] = "\0";
	// keeps track of how many digits have been put into Integer40 
	//int counter = 0, 
	int hex, offset = 0, len, i=0;
	
	// find the length of the string
	len = strlen(str);
	
	if (len < 40)
	{
		offset = 40 - len;
		
		// fill last offset indexes with 0
		while(i < offset)
		{
			num->digits[39-i] = 0;
			i++;
		}
		
	}
	
	
	// seg fault here
	i = 0;
	while(i < (40-offset) && str[i] != '\0' )
	{
		// confirm vald hex digit(not necessary)
		
		// convert char to string
		digit[0] = str[i]; 
		
		// convert to hex value int
		hex = strtol(digit,NULL,16);
		// put into data structure
		num->digits[39-offset-i] = hex;
		// increment index
		i++;
	}
	
	
	
	return num;
}

/*
Returns: A pointer to an Integer40 array of 40 random digits. If the input variable seed is set,
the random number generator will be seeded, otherwise not. Regardless, the 40 digits will be
initialized in 10 unique groups of 4 random digits. Returns NULL if there is an error during
creation or initialization of the hwConfigVariable.
*/
Integer40 *loadHWConfigVariable(int doSeed)
{
	// used for indexing
	int i,j, temp, nonSeed = rand()%1000;
	// Integer40 that will eventualy be returned
	Integer40 *config = NULL;
	int initSucess = initInteger40(&config);
	if (!initSucess)
	{
		return NULL;
	}
	
	// 
	if (doSeed != 0)
	{
		srand(time(NULL));
	}
	
	// generate 40 random hex digits 4 at a time and put them into config->digits
	// im not sure what it means by 10 unique groups of 4 digits
	// big 40-main02 says something about repeating every 5 digits for non seeded attepts
	// i think they mean 4 
	
	
	for(i = 0; i < 10; i++)
	{	
		// generate a 4 digit hex number and put it in the array
		if (doSeed !=0)
		{
			temp = rand()%0x1000;
		}
		else
		{
			temp = nonSeed;
		}
		//printf("%d\n",temp);
		
		//peel off digits and put themin data structure 
		for (j = 0 ; j < 4; j++)
		{
			config->digits[4*i + j] = temp%0x10; // come back to this --------------------------------
			temp = temp/0x10;
		}
	}
	return config;
}

/*
Returns A pointer to an Integer40 array of 40 random digits read in from the cryptoVariable-
Filename. Returns NULL if there is an error during initialization of the cryptoVariable or in
the file I/O.
*/
Integer40 *loadCryptoVariable(char *inputString)
{
	//open file
	FILE *in = NULL;
	in = fopen(inputString,"r");
	if (in == NULL)
	{
		fprintf(stderr,"Failed to open %s\n", inputString);
		return NULL;
	}
	
	// Integer 40 that will eventualy be returned
	Integer40 *crypto = NULL;
	int initSucess = initInteger40(&crypto);
	if (!initSucess)
	{
		return NULL;
	}
	
	// place to hold text read from file 
	char buffer[41];
	
	// read file into string
	fgets(buffer,41, in);
	// 
	crypto = parseString(buffer);
	
	return crypto;
}

// Helper functions--------------------------------------


/*
initalizes memory associated with Integer40 variable. returns 1 on sucess, 0 on failure. 
*/
int initInteger40(Integer40 **p)
{
	
	*p = calloc(1,sizeof(Integer40)); // dont forget to free this
	// confirm allocation
	if (*p == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		return 0;
	}
	// initalize digits
	(*p)->digits = calloc(1,sizeof(int)*40);
	// comfirm allocation
	if ((*p)->digits == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		free(p);
		return 0;
	}
	
	return 1;
}

