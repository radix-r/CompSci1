/*
Ross Wagner
ro520462
Homework3

The purpose of this program is to sort an amount of airPdata, read in from a csv, based on 
either their latitude or alphabetically 

I Ross Wagner (ro520462) affirm that this program is entirely my own work and that I have
neither developed my code together with any another person, nor copied any code from any other person,
nor permitted my code to be copied or otherwise used by any other person, nor have I copied, modified, or
otherwise used program code that I have found in any external source, including but not limited to, online
sources. I acknowledge that any violation of the above terms will be treated as academic dishonesty
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "airPdata.h"
#define NUMFIELDS 19
#define BUFFER_SIZE 256

void printData(airPdata airport);
void deleteStruct(airPdata *apd);
float sexag2decimal(char *degreeString);
int isHelipad(char *id);
void printAirports(airPdata *array, int size);

//
void sortByLocID(airPdata* airports, int first, int last);
void sortByLatitude(airPdata* airports, int first, int last);



int main(int argc, char ** argv)
{
	
	FILE* fid = NULL;
	// array to hold fields from csv
	char** fields = NULL; 
	// 
	char buffer[BUFFER_SIZE];
	//airPdata* airports = NULL;
	airPdata *airports = NULL;
	airPdata* tempAP = NULL;
	
	
	char sortPeram[2];
	int count = 0,i = 0, j=0;
	 
	// Check for command line input and open input file.
	if(argc==3){
		fid = fopen(argv[1], "r");
		if(fid==NULL)
		{
			printf("File %s failed to open. Aborting.\n", argv[1]);
			return 2;
		}
			
		// set sort peramiter
		strcpy(sortPeram, argv[2]);
		//printf("here\n");
		// confirm valid sort peramiter
		if(!(strcmp(sortPeram,"a") == 0 || strcmp(sortPeram,"n") == 0))
		{
			printf("Invalid sort peramiter '%s'\n",sortPeram);
			printf("Use 'a' for alphabetical or 'n' for North Bound Exit\n");
			printf("Syntax: ./hw3sort [input file] [sort peramiter]\n");
			return 1;
		}
	}
	else{
		printf("Incorect number of input parameters. Please specify the name of the input file and sort peramiter.\n");
		printf("Use 'a' for alphabetical or 'n' for North Bound Exit\n");
		printf("Syntax: ./hw3sort [input file] [sort peramiter]\n");
		return 1;
	}
	
		// Determine length of the file.
	while(fgets(buffer, BUFFER_SIZE, fid) != NULL){
		count++;
	}
	rewind(fid);
	
	//  allocate memory. calloc initilizes fields to null?
	airports = /*(airPdata*)*/ calloc(count, sizeof(airPdata));
	tempAP = /*(airPdata*)*/ calloc(1, sizeof(airPdata)); 
	fields = (char**) calloc(1,sizeof(char*)*NUMFIELDS);
	

	
	// comfirm allocation
	if (airports == NULL || fields == NULL || tempAP == NULL)
	{
		fprintf(stderr,"calloc() failed\n");
		return 1;
	}
	
	// print header for data
	printf("%-12s %-42s %-34s %-15s %-16s \n",
		"FAA Site", "Airport Name", "City", 
		"Latitude", "Longitude");
	printf("%-12s %-42s %-34s %-15s %-16s\n",
		"========", "============", "====", 
		"========", "=========");
	  
	// get data from csv
	while (	fgets(buffer,BUFFER_SIZE, fid) != NULL)
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
		//airport->siteNumber = fields[0];
		tempAP->locID = fields[1];
		tempAP->fieldName = fields[2];
		tempAP->city = fields[3];
		// airport->state = fields[4];
		tempAP->latitude = sexag2decimal(fields[8]); // convert field from sexagesimal string to decimal floating point
		tempAP->longitude = sexag2decimal(fields[9]);
		
		// print the contents of airport 
		//printData(airport);
		
	
		// discriminate against heli pads here
		if (!isHelipad(tempAP->locID))
		{
			//printData(tempAP);
			airports[i] = *tempAP; // data is getting distorted in array
			i++;
		}	
	}
	
	printAirports(airports, i);
	printf("\n");

	sortByLatitude(airports, 0, i-1);

	
	
	
	//print them
	printAirports(airports, i);
	// delete the avl tree
	
	// free calloced variables
	free(fields);
	//free(airports);
	free(tempAP);
	// close the file
	fclose(fid);
	
	// all done
	return 0;
	
	
	
}

/*
prints the contents of an airPdata variable
*/
void printData(airPdata airport)
{
	//fprintf(stdout, "%-12s ",airport->siteNumber);
	fprintf(stdout, "%-11s ", airport.locID);
	fprintf(stdout, "%-42s ", airport.fieldName);
	fprintf(stdout, "%-34s ", airport.city);
	//fprintf(stdout, "%-3s ", airport->state);
	fprintf(stdout, "%-15f ", airport.latitude);
	fprintf(stdout, "%-16f ", airport.longitude);
	//fprintf(stdout, "%c", airport->controlTower);
	printf("\n");
}


/*
prits airpdata array
*/
void printAirports(airPdata *array, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printData(array[i]);
		//array++;
	}
}


/*
Converts sexagesimal string to decimal floating point number

example input: 
30-42-18.0000N
degrees-minutes-sec.MilliArcSecDirection

needs to be robust enough to handel bogus data
returns 0.0 if data is invalid
*/
float sexag2decimal(char *degreeString)
{
	float sign;// 1.0 or -1.0 depending on direction
	float coordF[3]; // [0]:Degrees , [1]:Minutes, [2]:Seconds.MilliArcSeconds
	char *coordS[3];// [0]:Degrees , [1]:Minutes, [2]:Seconds.MilliArcSeconds
	int len = strlen(degreeString);
	int i,j;
	char direction;
	
	// remove last character, which should be direction
	// assign a variable to 1.0 or -1.0. mult with result at the end
	direction = tolower(degreeString[len-1]);
	degreeString[len-1] = '\0';
	
	if (direction == 'n' || direction == 'e')
	{
		sign = 1.0;
	}
	else if(direction == 's' || direction == 'w')
	{
		sign = -1.0;
	}
	else
	{
		printf("Invalid direction '%c'\n",direction);
		return 0.0;
	}
	
	// break string up by '-' delimiter
	for(i = 0; i < 2; i++)
	{
		if( (coordS[i] = strsep(&degreeString,"-")) == NULL )
		{
			return 0.0;
		}
	}
	// remaining string should be sec.milArcSec
	coordS[2] = degreeString;
	
	// determine if characters are numeric. if not return 0.0
	for(i = 0; i < 3; i++)
	{
		len = strlen(coordS[i]);
		for (j = 0; j < len; j++)
		if (!(isdigit(coordS[i][j]) || coordS[i][j] == '.'))
		{
			printf("Invalid coordinates\n");
			return 0.0;
		}
	}
	
	// use function atof() to convert sting to float
	for(i=0; i < 3; i++)
	{
		coordF[i] = atof(coordS[i]);
		// confirm that vales are within the valid range 
		if(i == 0)
		{
			if(coordF[i] > 180 || coordF < 0)
			{
				printf("Invalid range\n");
				return 0.0;
			}
		}
		else if (coordF[i] > 60 || coordF[i] < 0)
		{
			printf("Invalid range\n");
			return 0.0;	
		}	
	}
	
	// add corrosponding to (sign)*(DDD+ MM/60 + SS.MAS/(60^2))
	return (sign)*(coordF[0] + coordF[1]/60 + coordF[2]/(60*60));	 
}


/*
Check if airPdata is a helipad probably
*/
int isHelipad(char *id)
{
	int len = strlen(id);
	int i;
	
	//if the id has a number in it then it is probably a helipad
	for (i = 0; i < len; i++)
	{
		if (isdigit(id[i]))
		{
			return 1;
		}
	}
	return 0;
}


// sort functions ------------------------------------------------------------------

void sortByLocID(airPdata* airports, int first, int last)
{
}

void sortByLatitude(airPdata* airports, int first, int last)
{
	int pivot, j, i;
  	int temp;

  if (first<last) {
    pivot = first;
    i = first;
    j = last;

    while (i<j) {
      while ((airports[i].latitude) <= (airports[pivot].latitude) && i < last)
        i++;
      while ((airports[j].latitude) > (airports[pivot].latitude))
        j--;
      if (i < j) {
        temp = airports[i].latitude;
        airports[i].latitude = airports[j].latitude;
        airports[j].latitude = temp;
      }
    }

    temp = airports[pivot].latitude;
    airports[pivot].latitude = airports[j].latitude;
    airports[j].latitude = temp;
    sortByLatitude(airports, first, j - 1);
    sortByLatitude(airports, j + 1, last);

  }
}


