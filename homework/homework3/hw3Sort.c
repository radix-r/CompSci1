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

void parseLine(char *line, airPdata *apd);
void printData(int length, airPdata *apd);
void deleteStruct(airPdata *apd);
float sexag2decimal(char *degreeString);
int isHelipad(char *id);
void sortByLatitude(airPdata* airports, int first, int last);
void sortByLocID(airPdata* airports, int first, int last);

#define BUFFER_SIZE 500

int main (int argc, char *argv[]){

	// Declare input buffer and other parameters
	FILE *fid;
	char buffer[BUFFER_SIZE];
	int count = 0, notPads = 0;
	char sortPeram[2];
	
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
	
	
	// Declare a struct array and allocate memory.
	airPdata *data;
	// place to put only airports
	airPdata *airports;
	data = malloc(sizeof(airPdata)*count);
	airports = malloc(sizeof(airPdata)*count);
	
	if(data==NULL || airports==NULL){
		printf("Memory allocation for airPdata array failed. Aborting.\n");
		return 2;
	}

	// Read and parse each line of the inputt file.
	for(int i = 0; i<count; i++){
		fgets(buffer, BUFFER_SIZE, fid);
		
		// fgets() includes the New Line delimiter in the output string. 
		// i.e. "This is my string.\n\0"
		// We will truncate the string to drop the '\n' if it is there.
		// Note: There will be no '\n' if the line is longer than the buffer.
		if(buffer[strlen(buffer) - 1] == '\n') buffer[strlen(buffer)-1] = '\0';
		
		parseLine(buffer, data+i);
	}
	
	// close the input file.
	fclose(fid);
	
	//remove helipadas
	for(int i = 0; i<count;i++)
	{
		if (!isHelipad(data[i].LocID))
		{
			//printData(tempAP);
			airports[notPads] = data[i];
			notPads++;
			//printf("here\n");
		}
	}
	// sort
	if (strcmp(sortPeram, "n") == 0)
	{
		sortByLatitude(airports, 0, notPads-1);
	}
	else
	{
		sortByLocID(airports, 0, notPads-1);
	}
	
	
	
	// Output the data to stdout.
	printData(notPads, airports);

	// Free the memory used for fields of the structs.
	for(int i=0; i<count; i++){
		deleteStruct(data+i);
		
	}

	// Free the memory for the struct array.
	free(data);
	free(airports);
	return 0;

}


void parseLine(char *line, airPdata *apd){

	int i=0, j=0, commas=0;
	
	while(commas<15){
		while(*(line+i)!=','){
			i++;
		}
		
		// strncpy does not append a '\0' to the end of the copied sub-string, so we will
		// replace the comma with '\0'. 
		*(line+i) = '\0';

		switch (commas){
		case 1:   //Grab the second "field" - Location ID
			apd->LocID = malloc(sizeof(char)*(i-j+1));
			if(apd->LocID==NULL){
                        	printf("malloc failed to initialize airPdata.LocID.\n");
                                exit(-1);
                        }
                        strncpy(apd->LocID, line+j, i-j+1);
                        break;
		case 2:   //Grab the third "field" - Field Name
			apd->fieldName = malloc(sizeof(char)*(i-j+1));
			if(apd->fieldName==NULL){
				printf("malloc failed to initialize airPdata.fieldName.\n");
				exit(-1);
			}
			strncpy(apd->fieldName, line+j, i-j+1);
			break;
		case 3:   //Grab the fourth "field" - City
			apd->city = malloc(sizeof(char)*(i-j+1));
			if(apd->city==NULL){
				printf("malloc failed to initialize airPdata.city.\n");
				exit(-1);
			}
			strncpy(apd->city, line+j, i-j+1);
			break;
		
		case 8:   //Grab the ninth "field" - Latitude (sexagesimal string)
			// convert to float here ---------------------------------------
			apd->latitude =sexag2decimal(line+j);
			break;
		case 9:   //Grab the tenth "field" - Longitude (sexagesimal string)
			// convert to float here ---------------------------------------
			apd->longitude =sexag2decimal(line+j);
			break;
	
		}

		j=++i;
		commas++;
	}
}

void printData(int length, airPdata *data){
	printf("code,name,city,lat,lon\n");
	for(int i=0; i<length; i++){
		printf("%s,%s,%s,%.4f,%.4f\n",(data+i)->LocID,(data+i)->fieldName,
		  (data+i)->city,(data+i)->latitude,(data+i)->longitude);
	}
}

void deleteStruct(airPdata *apd){
	//free(apd->longitude);
	//free(apd->latitude);
	free(apd->city);
	free(apd->fieldName);
	free(apd->LocID);
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
		fprintf(stderr,"Invalid direction '%c'\n",direction);
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
			fprintf(stderr,"Invalid coordinates\n");
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
				fprintf(stderr,"Invalid range\n");
				return 0.0;
			}
		}
		else if (coordF[i] > 60 || coordF[i] < 0)
		{
			fprintf(stderr,"Invalid range\n");
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

void sortByLatitude(airPdata* airports, int first, int last)
{
	int pivot, j, i;
  	airPdata temp;

  if (first<last) {
    pivot = first;
    i = first;
    j = last;

    while (i<j) 
	{
      while ((airports[i].latitude) <= (airports[pivot].latitude) && i < last)
        i++;
      while ((airports[j].latitude) > (airports[pivot].latitude))
        j--;
      if (i < j) 
	  {
        temp = airports[i];
        airports[i] = airports[j];
        airports[j] = temp;
      }
    }

    temp = airports[pivot];
    airports[pivot] = airports[j];
    airports[j] = temp;
    sortByLatitude(airports, first, j - 1);
    sortByLatitude(airports, j + 1, last);

  }
}

void sortByLocID(airPdata* airports, int first, int last)
{
	int pivot, j, i;
  	airPdata temp;

  if (first<last) {
    pivot = first;
    i = first;
    j = last;

    while (i<j) 
	{
      while (strcmp(airports[i].LocID, airports[pivot].LocID) <=0 && i < last)
        i++;
      while (strcmp(airports[j].LocID, airports[pivot].LocID) > 0)
        j--;
      if (i < j) 
	  {
        temp = airports[i];
        airports[i] = airports[j];
        airports[j] = temp;
      }
    }

    temp = airports[pivot];
    airports[pivot] = airports[j];
    airports[j] = temp;
    sortByLocID(airports, first, j - 1);
    sortByLocID(airports, j + 1, last);

  }
}


