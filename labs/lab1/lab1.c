/*
Ross Wagner
LAB 1
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	char cwd[1024];
	char un[1024];	
	
	fprintf(stdout, "Ross Wagner\n");
	
	// get username
	fprintf(stdout,"Username: %s\n", getenv("USER"));
	
	//get working dir
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		fprintf(stdout, "Current working dir: %s\n", cwd);
		
	else
		perror("getcwd() error"); 
	return 0;
}
