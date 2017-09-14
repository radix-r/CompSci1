/*
Ross Wagner

I Ross Wagner (ro520462) affirm that this program is entirely my own work and that I have
neither developed my code together with any another person, nor copied any code from any other person,
nor permitted my code to be copied or otherwise used by any other person, nor have I copied, modified, or
otherwise used program code that I have found in any external source, including but not limited to, online
sources. I acknowledge that any violation of the above terms will be treated as academic dishonesty

*/



/* Recap left & right rotations (simple case)
T1, T2 and T3 are subtrees of the tree rooted with y (on left side) 
or x (on right side)           
                y                               x
               / \     Right Rotation          /  \
              x   T3   - - - - - - - >        T1   y 
             / \       < - - - - - - -            / \
            T1  T2     Left Rotation            T2  T3
Keys in both of the above trees follow the following order 
      keys(T1) < key(x) < keys(T2) < key(y) < keys(T3)
So BST property is not violated anywhere.
*/

#include<stdio.h>
#include<stdlib.h>
#include <string.h> // strcmp()

/*****
  Modifying the data stored in the AVL tree?
  1. Start with the structure shown below.
  2. Sort out the data type and any additional data that should be there.
  3. Maybe even add a struct to support the requirements.
      a. All data types can be put in the struct 
         BUT
      b. Make sure that there is a valid data type that can be arithmetically
         compared so as to maintain the integrity of the AVL tree. 
  4. Make sure to check all the locations that manage the "key".
 *****/

// An AVL tree node
struct node
{
    float key;
    struct node *left;
    struct node *right;
    int height;
};
 
// A utility function to get maximum of two integers
int max(float a, float b);
 
// A utility function to get height of the tree
int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two integers
int max(float a, float b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct node* newNode(float key)
{
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
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
 
struct node* insert(struct node* node, float key)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));
 
    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);
 
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
    if (balance > 1 && key < node->left->key)
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
    if (balance < -1 && key > node->right->key)
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
    if (balance > 1 && key > node->left->key)
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
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
// A utility function to print preorder traversal of the tree.
// The function also prints height of every node
void preOrder(struct node *root)
{
    if(root != NULL)
    {
      printf("%.4f\n", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}



// A utility function to print inorder traversal of the tree.
void inOrder(struct node *root)
{
    if(root != NULL)
    {
    	inOrder(root->left);
		
      	printf("%.4f\n", root->key);
        
        inOrder(root->right);
    }
}

// A utility function to print reveresed order traversal of the tree.
void revOrder(struct node *root)
{
	if (root != NULL)
	{
		revOrder(root->right);
		printf("%.4f\n", root->key);
		revOrder(root->left);
	}
}

/*
  The main function below is the test harness for the AVL tree code above.
 
  Any modifications to support alternative input modes, like STDIN, will
  happen here.

 */

/* Driver program to test above functions*/
int main(int argc, char *argv[])
{
  
  
  struct node *root = NULL;
  char *line = NULL;  // buffer to hold input on stdin
  char *sp = NULL; // start pointer for parsing line
  char *ep = NULL; // endpointer for parsing line
  int cnt = 0; //counter for floats
  float flt = 0.0; //variable to hold float
  
  // confirm proper number of arguments
  if (argc != 2 || !( strcmp(argv[1],"a") == 0 || strcmp(argv[1],"d")==0 ) )
  {
  	fprintf(stderr, "Incorect number of input parameters. Please specify the sort order\n");
  	fprintf(stderr, "'a' for ascending, 'd' for descending.\n");
	fprintf(stderr,"Syntax: ./AVLsort [sort order]\n");
	
	return 1;
  }
  
  //printf("\n%s\n",argv[1]);
 
 
  //read from floating point numbers from sdtin untill  
  while (scanf("%m[^\n]%*c", &line) >=1)
  {
  	cnt = 0;
  	sp = line;
  	while(*sp)
  	{
  		flt = strtof(sp, &ep);			 /* convert value to float           */
  		{
  			if(sp != ep)				 /* test that strtof processed chars */
  			{
  				sp = ep;				/* set sp to ep for next value      */
  				root = insert(root, flt);/* insert float into avl tree */
  				cnt++;					 /* increase float count             */
			}
			else
			{
				break;
			}
			sp++;						 /* skip space or comma separator    */	
		}
	}
  }
  if(line) free(line);					 /* free memory allocated by scanf   */
  
  
  
  
  
  // if 'a' print in pre order
  if (strcmp(argv[1],"a") == 0)
  {
    //printf("ascending\n");
  	inOrder(root);
  	//printf("\n"); 
  
  }
  // if 'd' print in post order
  else if(strcmp(argv[1],"d") == 0)
  {
  	//printf("decending\n");
  	revOrder(root);
  	//printf("\n"); 
  
  }
  
  
 
  return 0;
}
