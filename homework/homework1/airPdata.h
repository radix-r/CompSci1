/*
Header file for hw1etl.c 
*/

typedef struct airPdata
{
	char *siteNumber; //FAA Site Number
	char *locID; //Airport’s ‘‘Short Name’’, \textit{e.g.} MCO
	char *fieldName; //Airport Name
	char *city; //Associated City
	char *state; //State
	char *latitude; //Latitude
	char *longitude; //Longitude
	char controlTower;//Control Tower, this is a single character (Y/N)
} airPdata;
