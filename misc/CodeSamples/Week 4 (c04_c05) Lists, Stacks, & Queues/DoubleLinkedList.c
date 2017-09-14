/* Double linked List functions */
/*****************************************************
Name: DoubledLinked.c
version: 0.1
Description:  Implementation of a DoubleLinkedList.
These functions provide functionality of a double linked  List.
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
******************************************************/
#include "DoubleLinkedList.h"
#include "stdlib.h"
#include "stdio.h"

/* Declare pHead */
DoubleLinkedList* pHead = NULL;

/* Variable for storing error status */
unsigned int Error = NOERROR;

DoubleLinkedList* GetNodeData(DoubleLinkedList* pNode)
{
    if(!(pNode))
    {
        Error = MEMALLOCERROR;
        return NULL;
    }
   else
   {
    printf("\nEnter a number: ");
    scanf("%d",&pNode->number);
    return pNode;
   }
}

/* Add a node forward */
void AddNodeForward(void)
{
    DoubleLinkedList* pNode = malloc(sizeof(DoubleLinkedList));
    pNode = GetNodeData(pNode);
    if(pNode)
    {
    DoubleLinkedList* pCurrent = pHead;
    if (pHead== NULL)
    {
        pNode->pNext= NULL;
        pNode->pPrevious= NULL;
        pHead=pNode;
    }
    else
    {
      while(pCurrent->pNext!=NULL)
      {
        pCurrent=pCurrent->pNext;
      }
      pCurrent->pNext= pNode;
      pNode->pNext= NULL;
      pNode->pPrevious= pCurrent;
    }
    }
    else
    {
        Error = MEMALLOCERROR;
    }

}

/* Function to add nodes in reverse direction,
Arguments; Node to be added.
Returns : Nothing
*/
void AddNodeReverse(void)
{
    DoubleLinkedList* pNode =  malloc(sizeof(DoubleLinkedList));
    pNode = GetNodeData(pNode);
    if(pNode)
    {
    DoubleLinkedList* pCurrent =  pHead;
    if (pHead==NULL)
    {
        pNode->pPrevious= NULL;
        pNode->pNext= NULL;
        pHead=pNode;
    }
    else
    {
     while(pCurrent->pPrevious != NULL )
     {
        pCurrent=pCurrent->pPrevious;
     }
    pNode->pPrevious= NULL;
    pNode->pNext= pCurrent;
    pCurrent->pPrevious= pNode;
    pHead=pNode;
    }
    }
    else
    {
        Error = MEMALLOCERROR;
    }


}

/* Display Double linked list data in forward direction */
void DisplayNodeForward(void)
{
    DoubleLinkedList* pCurrent =  pHead;
    if (pCurrent)
    {
     while(pCurrent != NULL )
      {
            printf("\nNumber in forward direction is %d ",pCurrent->number);
            pCurrent=pCurrent->pNext;
      }
    }
    else
    {
          Error = LISTEMPTY;
          ErrorMessage(Error);
    }
}

/* Display Double linked list data in Reverse direction  */
void DisplayNodeReverse(void)
{
    DoubleLinkedList* pCurrent =  pHead;
    if (pCurrent)
    {
      while(pCurrent->pNext != NULL)
      {
        pCurrent=pCurrent->pNext;
      }
      while(pCurrent)
      {
        printf("\nNumber in Reverse direction is %d ",pCurrent->number);
        pCurrent=pCurrent->pPrevious;
      }
    }
    else
    {
       Error = LISTEMPTY;
       ErrorMessage(Error);
    }

}

/* Delete nodes in a double linked List */
void DeleteNode(const int SearchNumber)
{
    unsigned int Nodefound = FALSE;
    DoubleLinkedList* pCurrent =  pHead;
    if (pCurrent != NULL)
    {
    DoubleLinkedList* pNextNode =  pCurrent->pNext;
    DoubleLinkedList* pTemp = (DoubleLinkedList* ) NULL;

    if (pNextNode != NULL)
    {
    while((pNextNode != NULL) && (Nodefound==FALSE))
    {
      // If search entry is at the beginning
      if(pHead->number== SearchNumber)
       {
        pCurrent=pHead->pNext;
        pHead= pCurrent;
        pHead->pPrevious= NULL;
        Nodefound =TRUE;
       }
       /* if the search entry is somewhere in the DoubleLinkedList or at the end */
      else if(pNextNode->number == SearchNumber)
        {
           Nodefound = TRUE;
           pTemp = pNextNode->pNext;
           pCurrent->pNext = pTemp;

            /* if the node to be deleted is not NULL,,,
            then point pNextnode->pNext to the previous node
            which is pCurrent */
           if(pTemp)
           {
               pTemp->pPrevious= pCurrent;
           }
          free(pNextNode);
        }
      /* iterate through the Double Linked List until next node is NULL  */
      pNextNode=pNextNode->pNext;
      pCurrent=pCurrent->pNext;
    }

    }
    else if (pCurrent->number == SearchNumber)
    {
        /* add code to delete nodes allocated with other functions if
         the search entry is found.
         */
        Nodefound = TRUE;
        free(pCurrent);
        pCurrent= NULL;
        pHead = pCurrent;
    }

    }
    else if (pCurrent == NULL)
    {
        Error= LISTEMPTY;
        ErrorMessage(Error);
    }
    if (Nodefound == FALSE && pCurrent!= NULL)
    {
       Error = NODENOTFOUND;
       ErrorMessage(Error);
    }

}

/* Function to detect cycle in double linked List */
unsigned int DetectCycleinList(void)
{
    DoubleLinkedList* pCurrent = pHead;
    DoubleLinkedList* pFast = pCurrent;
    unsigned int cycle = FALSE;
    while( (cycle==FALSE) && pCurrent->pNext != NULL)
    {
        if(!(pFast = pFast->pNext))
        {
        cycle= FALSE;
        break;
        }
        else if (pFast == pCurrent)
        {
        cycle = TRUE;
         break;
        }
        else if (!(pFast = pFast->pNext))
        {
           cycle = FALSE;
           break;

        }
        else if(pFast == pCurrent)
        {
            cycle = TRUE;
            break;

        }
        pCurrent=pCurrent->pNext;
    }
    if(cycle)
    {
        printf("\nDouble Linked list is cyclic");
    }
    else
    {
        Error=LISTEMPTY;
        ErrorMessage(Error);
    }
    return cycle;
}

/*Function to reverse nodes in a double linked list */
void ReverseNodes(void)
{
 DoubleLinkedList *pCurrent= NULL, *pNextNode= NULL;
 pCurrent = pHead;
 if (pCurrent)
 {
  pHead = NULL;
  while (pCurrent != NULL)
   {
     pNextNode = pCurrent->pNext;
     pCurrent->pNext = pHead;
     pCurrent->pPrevious=pNextNode;
     pHead = pCurrent;
     pCurrent = pNextNode;
   }
 }
 else
 {
     Error= LISTEMPTY;
     ErrorMessage(Error);
 }
}

/* Function to display diagnostic errors */
void ErrorMessage(int Error)
 {
     switch(Error)
     {
         case LISTEMPTY:
         printf("\nError: Double linked list is empty!");
         break;

         case MEMALLOCERROR:
         printf("\nMemory allocation error ");
         break;

         case NODENOTFOUND:
         printf("\nThe searched node is not found ");
         break;

         default:
         printf("\nError code missing\n");
         break;
     }
 }
