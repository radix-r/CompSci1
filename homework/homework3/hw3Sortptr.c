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


// An AVL tree node
typedef struct node
{
    airPdata *key;
    struct node *left;
    struct node *right;
    int height;
}AVLnode;
 

void printData(airPdata* airport);
void deleteStruct(airPdata *apd);
float sexag2decimal(char *degreeString);
int isHelipad(char *id);
// AVL tree functions
int max(int a, int b);
int height(AVLnode *N);
AVLnode* newNode(airPdata *key);
AVLnode *rightRotate(AVLnode *y);
AVLnode *leftRotate(AVLnode *x);
int getBalance(AVLnode *N);
AVLnode* insert(AVLnode* node, airPdata *key, char *sortPeram);
void inOrder(AVLnode *root);
void freeTree(AVLnode *root);
//
void sortByLocID(AVLnode *airPtree);
void sortByLatitude(AVLnode *airPtree);



int main(int argc, char ** argv)
{
	
	FILE* fid = NULL;
	// array to hold fields from csv
	char** fields = NULL; 
	// 
	char buffer[256];
	airPdata* airport = NULL;
	 
	AVLnode * airPtree = NULL;
	
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
	
	//  allocate memory. calloc initilizes fields to null?
	airport = calloc(1, sizeof(airPdata));
	fields = (char**) calloc(1,sizeof(char*)*NUMFIELDS);
	

	
	// comfirm allocation
	if (airport == NULL || fields == NULL)
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
	while (	fgets(buffer,256, fid) != NULL)
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
		airport->locID = fields[1];
		airport->fieldName = fields[2];
		airport->city = fields[3];
		// airport->state = fields[4];
		airport->latitude = sexag2decimal(fields[8]); // convert field from sexagesimal string to decimal floating point
		airport->longitude = sexag2decimal(fields[9]);
		
		// print the contents of airport 
		//printData(airport);
		
		// add avl tree
		// discriminate against heli pads here
		if (!isHelipad(airport->locID))
		{
			printData(airport);
			airPtree = insert(airPtree,airport, sortPeram);
		}	
	}
	

	printf("\n");
	
	//print them
	inOrder(airPtree);
	
	// delete the avl tree
	freeTree(airPtree);// remember to free data in nodes
	// free calloced variables
	free(fields);
	free(airport);
	// close the file
	fclose(fid);
	
	// all done
	return 0;
	
	
	
}

/*
prints the contents of an airPdata variable
*/
void printData(airPdata* airport)
{
	//fprintf(stdout, "%-12s ",airport->siteNumber);
	fprintf(stdout, "%-11s ", airport->locID);
	fprintf(stdout, "%-42s ", airport->fieldName);
	fprintf(stdout, "%-34s ", airport->city);
	//fprintf(stdout, "%-3s ", airport->state);
	fprintf(stdout, "%-15f ", airport->latitude);
	fprintf(stdout, "%-16f ", airport->longitude);
	//fprintf(stdout, "%c", airport->controlTower);
	printf("\n");
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


// AVL tree functions ------------------------------------------------------------------

 
// A utility function to get height of the tree
int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two ints
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
AVLnode* newNode(airPdata *key)
{
    AVLnode* node = (AVLnode*) malloc(sizeof(AVLnode));
    
    //node->key = (airPdata*) malloc(sizeof(airPdata));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}
 
/* 
 * RECAP Balance is based on Height
 *     Hn = Hl - Hr 
 * so 
 *    positive => LEFT HEAVY
 *    negative => RIGHT HEAVY
 */
// Get Balance factor of node N
int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
AVLnode* insert(AVLnode* node, airPdata *key, char *sortPeram)
{
    /* 1.  Perform the normal BST insertion */
    // instert b
	if (node == NULL)
        return(newNode(key));
 
    if (key->latitude < node->key->latitude)
        node->left  = insert(node->left, key, sortPeram);
    else
        node->right = insert(node->right, key, sortPeram);
 
    /* 2. Update height of this ancestor node */
    node->height = max(height(node->left), height(node->right)) + 1;
 
    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes UNBALANCED, then there are 4 cases
    
    /* CASE # 1 => LEFT-LEFT aka left?
       T1, T2, T3 and T4 are subtrees.
         z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2
     */
    // Left Left Case in code
    if (balance > 1 && key->latitude < node->left->key->latitude)
        return rightRotate(node);
    
    /* Case #2 => RIGHT-RIGHT aka right?

       z                                y
      /  \                            /   \ 
     T1   y     Left Rotate(z)       z      x
      /  \   - - - - - - - ->    / \    / \
	T2   x                     T1  T2 T3  T4
       / \
     T3  T4

     */
    // Right Right Case in code
    if (balance < -1 && key->latitude > node->right->key->latitude)
        return leftRotate(node);

    
    /* CASE # 3 => LEFT-RIGHT aka left-right?
     z                               z                           x
    / \                            /   \                        /  \ 
   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
    / \                        / \
  T2   T3                    T1   T2

    */
    // Left Right Case in code
    if (balance > 1 && key->latitude > node->left->key->latitude)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
    /* CASE #4 = RIGHT-LEFT aka right-left?
        z                            z                            x
       / \                          / \                          /  \ 
      T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
      / \   - - - - - - - - ->     /  \      - - - - - - - ->  / \    /	\
    x   T4                       T2    y                      T1  T2  T3  T4
   / \                                /  \
 T2   T3                             T3   T4   
     */
    // Right Left Case in code
    if (balance < -1 && key->latitude < node->right->key->latitude)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}



// A utility function to print inorder traversal of the tree.
// prints from least to greatest
void inOrder(AVLnode *root)
{
    if(root != NULL)
    {
    	inOrder(root->left);
		
      	printData(root->key);
        
        inOrder(root->right);
    }
}


void sortByLocID(AVLnode *airPtree)
{

}
void sortByLatitude(AVLnode *airPtree)
{
	
}

/*
traverse tree and free nodes
*/
void freeTree(AVLnode *root)
{
	if (root != NULL)
	{
		
		freeTree(root->left);
		freeTree(root->right);
		//free(root->key);
		free(root);

	}
}

