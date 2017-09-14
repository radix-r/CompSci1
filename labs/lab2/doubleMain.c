/***************************************************
Name: main.c
version: 0.1
Description:  Implementation of a double linked list

Change history:
0.1 Initial version
License: GNU GPL v3


Lab Problem #2 Objective:
1. Given that pHead is a global variable declared in
   DoubleLinkedList.c - rewrite all the functions that
   use pHead to accept a passed parameter that points
   to the head of the doubly-linked list used in the 
   code examples in the following modules:
    a. DoubleLinkedList.c
    b. DoubleLinkedList.h
    c. doubleMain.c (if necessary)
    d. doubleMain.h (if necessary)

Lab Problem #2 Suggestions:
1. Make sure the four modules listed in items 1a thru 1d
   above are in the SAME directory.
2. Compile with the command:
   gcc DoubleLinkedList.c doubleMain.c -o doubleListX
3. Test with a few simple steps.
4. Start working on the objective 1 above by editing the
   appropriate modules.
****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "doubleMain.h"

int main(void)
{
	/* Declare pHead */
    DoubleLinkedList* pHead = NULL;
    int choice =0;
    int InputNumber=0;
    printf("\nThis program creates a double linked list");
    printf("\nYou can add nodes in forward and reverse directions");
    do
    {
        printf("\n1.Create Node Forward");
        printf("\n2.Create Node Reverse");
        printf("\n3.Delete Node");
        printf("\n4.Display Nodes in forward direction");
        printf("\n5.Display Nodes in reverse direction");
        printf("\n6.Reverse nodes");
        printf("\n7.Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
              case 1:
              AddNodeForward(&pHead);
              break;

              case 2:
              AddNodeReverse(&pHead);
              break;

              case 3:
              printf("\nEnter the node you want to delete: ");
              scanf("%d",&InputNumber);
              DeleteNode(InputNumber,&pHead);
              break;

              case 4:
              printf("\nDisplaying node data in forward direction \n");
              DisplayNodeForward(&pHead);
              break;

              case 5:
              printf("\nDisplaying node data in reverse direction\n");
              DisplayNodeReverse(&pHead);
              break;

              case 6:
              ReverseNodes(&pHead);
              break;

              case 7:
              printf("Exiting program");
              break;

              default:
              printf("\nIncorrect choice\n");
         }

    } while (choice !=7);
    return 0;
}
