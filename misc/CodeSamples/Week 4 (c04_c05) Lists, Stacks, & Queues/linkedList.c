/*
 * Recursive C program to display members of a linked list
 */
#include <stdio.h>
#include <stdlib.h>

struct node
{
  int a;
  struct node *next;
};

void generate(struct node **);
void display(struct node*);
void delete(struct node **);

int main()
{
  struct node *head = NULL;
  printf("the contents of the  pointer named head = %p\n",head);
    printf("the contents of the  address named head = %p\n",&head);
  generate(&head);
  display(head);
  delete(&head);

  return 0;
}


void generate(struct node **fred)
{
    printf("the contents of the  P2P named fred = %p\n",*fred);
  int num = 10, i;
  struct node *temp;
  
  for (i = 0; i < num; i++)
    {//cast the malloc'd buffer to a pointer of a node 
      temp = (struct node *)malloc(sizeof(struct node));
      temp->a = i;
      if (*fred == NULL)
	{
	  *fred = temp; // put the next node on the list
	  (*fred)->next = NULL; // end the list
	}
      else
	{
	  temp->next = *fred; //not null so skip afred
	  *fred = temp; //node is on the list
	}
    }
}

void display(struct node *head)
{
  printf("%2d %p\n ", head->a, head->next); // display the data
  // End of the line when NULL
  if (head->next == NULL)
    {
      printf("done w. display\n");
      return; // so go home...
    }
  display(head->next); // othewise do it again!
}

void delete(struct node **head)
{
  struct node *temp;
  while (*head != NULL) // what is head pointing to?
    {
      temp = *head; //make temp the old head of next
      *head = (*head)->next; // point to new head
      free(temp); // free the first head
    }
}
