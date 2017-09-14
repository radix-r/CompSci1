/*
homework 1
Ross Wagner
the goal of this program is to extract data from a csv file and print it

I Ross Wagner (ro520462) affirm that this program is entirely my own work and that I have
neither developed my code together with any another person, nor copied any code from any other person,
nor permitted my code to be copied or otherwise used by any other person, nor have I copied, modified, or
otherwise used program code that I have found in any external source, including but not limited to, online
sources. I acknowledge that any violation of the above terms will be treated as academic dishonesty
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airPdata.h"
#define NUMFIELDS 19
void printData(airPdata* airport);

int main(int argc, char ** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Proper usage: ./etl input.csv\n");
		return 1;
	}
	
	
	FILE* infile = NULL;
	char* filename = argv[1];
	// array to hold fields from csv
	char** fields = calloc(1,sizeof(char*)*NUMFIELDS); 
	// 
	char buffer[256];
	 
	// open the file 
	infile=fopen(filename, "r");
	// confirm opening
	if (infile == NULL)
	{
		fprintf(stderr,"Failed to open %s\n", filename);
		return 1;
	}
	
	//  allocate memory. calloc initilizes fields to null?
	airPdata* airport = calloc(1, sizeof(airPdata));
	
	// comfirm allocation
	if (airport == NULL)
	{
		fprintf(stderr,"calloc() failed\n");
		return 1;
	}
	
	// print header for data
	printf("%-12s %-11s %-42s %-34s %-3s %-15s %-16s Tower\n",
		"FAA Site", "Short Name", "Airport Name", "City", "ST",
		"Latitude", "Longitude");
	printf("%-12s %-11s %-42s %-34s %-3s %-15s %-16s =====\n",
		"========", "==========", "============", "====", "==",
		"========", "=========");
	  
	// get data from csv
	while (	fgets(buffer,256, infile) != NULL)
	{	
		// 
		char *line = buffer;
		char* field;
		int index = 0;
		// devide line by ,
		while((field = strsep(&line,",")) !=NULL )
		{
			// put field in apropriate place in fields array
			fields[index++] = field;
		}
		
		// load desired data into the struct
		airport->siteNumber = fields[0];
		airport->locID = fields[1];
		airport->fieldName = fields[2];
		airport->city = fields[3];
		airport->state = fields[4];
		airport->latitude = fields[8];
		airport->longitude = fields[9];
		// assume no tower data means no tower
		if (fields[14][0] == '\0')
		{
			airport->controlTower = 'N';
		}
		else
		{
			airport->controlTower = fields[14][0];
		}
		
		// print the contents of airport 
		printData(airport);
	}
	
	
	// free calloced variables
	free(fields);
	free(airport);
	// close the file
	fclose(infile);
	
	// all done
	return 0;
	
	
	
}

/*
prints the contents of an airPdata variable
*/
void printData(airPdata* airport)
{
	fprintf(stdout, "%-12s ",airport->siteNumber);
	fprintf(stdout, "%-11s ", airport->locID);
	fprintf(stdout, "%-42s ", airport->fieldName);
	fprintf(stdout, "%-34s ", airport->city);
	fprintf(stdout, "%-3s ", airport->state);
	fprintf(stdout, "%-15s ", airport->latitude);
	fprintf(stdout, "%-16s ", airport->longitude);
	fprintf(stdout, "%c", airport->controlTower);
	printf("\n");
}

