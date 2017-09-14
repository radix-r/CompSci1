//Adam Doussan AD844156 07/18/2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int power(int a, int b)
{
	if(b == 0)
		return 1;

	int i;
	int ans = a;

	for(i = 0; i < b-1; i++)
		ans *= a;

	return ans;
}

// Assumes hex isnt null

// For those that were here, everything in here was correct, my power function
// returned 16 for 16^0, which is obviously supposed to be 1. Also, check out
// how I would have done this in getValBetter()
int getVal(char hex [], int len)
{
	int retVal = 0;

	int i, count = 0;
	for(i = len - 1; i >= 0; i--)
	{
		int temp = 0;

		// Lowercase letter
		if(hex[i] >= 'a' && hex[i] <= 'f')
		{
			temp = hex[i] - 'a' + 10;
		}

		// Digit
		else if(hex[i] >= '0' && hex[i] <= '9')
		{
			temp = hex[i] - '0';
		}

		retVal += power(16, count) * temp;
		count++;
	}

	return retVal;
}

// works for all bases up to base 36
int getValBetter(char val [], int len, int base)
{
	int retVal = 0;

	for(int i = 0; i < len; i++)
	{
		retVal *= base;

		// Lowercase letter
		if(val[i] >= 'a' && val[i] <= 'z')
		{
			retVal += val[i] - 'a' + 10;
		}

		// Digit
		else if(val[i] >= '0' && val[i] <= '9')
		{
			retVal += val[i] - '0';
		}
	}

	return retVal;
}

char* getHex(int val)
{
	return NULL;
}

int main(int argc, char** argv)
{
	char hex [] = "12345f";
	int val = 0x12345f;

	printf("%d\n", getVal(hex, strlen(hex)));
	printf("%d\n", getValBetter(hex, strlen(hex), 16));
	//printf("%s\n", getHex(val));
}
