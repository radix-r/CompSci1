/*
Description:
Double linked list header file
License: GNU GPL v3

*/
#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

/* Codes for various errors */
#define NOERROR 0x0
#define MEMALLOCERROR 0x01
#define LISTEMPTY 0x03
#define NODENOTFOUND 0x4

/* True or false */
#define TRUE 0x1
#define FALSE 0x0

/* Double linked DoubleLinkedList definition */
 typedef struct DoubleLinkedList
{
    int number;
    struct DoubleLinkedList* pPrevious;
    struct DoubleLinkedList* pNext;
}DoubleLinkedList;

/* Get data for each node */
extern DoubleLinkedList* GetNodeData(DoubleLinkedList* pNode);

/*  Add a new node forward */
extern void AddNodeForward(void);

/* Add a new node in the reverse direction */
extern void AddNodeReverse(void);

/* Display nodes in forward direction */
extern void DisplayNodeForward(void);

/*Display nodes in reverse direction */
extern void DisplayNodeReverse(void);


/* Delete nodes in the DoubleLinkedList by searching for a node */
extern void DeleteNode(const int number);

/* Function to detect cycle in a DoubleLinkedList */
extern unsigned int DetectCycleinList(void);

/*Function to reverse nodes */
extern void ReverseNodes(void);

/* function to display error message that DoubleLinkedList is empty */
void ErrorMessage(int Error);

/* Sort nodes */
extern void SortNodes(void);

#endif
