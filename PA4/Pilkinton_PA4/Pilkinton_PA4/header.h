/************************************************************************
NAME: RADE PILKINTON
CLASS: CPTS 122 FALL 2017
DATE: 10/04/17
ASSIGNMENT: PA4
DESCRIPTION: This program simulates a grocery store with an express line and normal line. This is the header file.
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct data
{
	int customerNumber; // Unique identifier; starts at 1; after 24 hours should be reset to 1
	int serviceTime;   // Random time; varies between express and normal lanes; units in minutes
	int totalTime;     // totalTime = serviceTime + sum of serviceTimes of customers in line before this customer; units in minutes
} Data; // This memory needs to be allocated on the heap!

typedef struct grocerynode //Bonus
{
	char groceries[1000];
	struct GroceryNode *NextItem;
} GroceryNode;

typedef struct queueNode
{
	Data *pData;    // The memory for Data will need to be allocated on the heap as well!
	GroceryNode *gNext; //Bonus
	struct queueNode *pNext;
} QueueNode;

typedef struct queue
{
	QueueNode *pFront; //I understand Front and Rear better than Head and Tail for some reason.
	QueueNode *pRear;
} Queue;



int getN();

QueueNode *makeNode(Data newItem);

int enqueue(Queue *pQ, Data newItem);

struct Queue *CreateQueue();

int DeQueue(Queue *pQ);

void PrintQueue(Queue *pQ, int WhichLine, int StartOrEnd, int ArrivalTime);

int isEmpty(Queue *pQ);

void PrintGroceries(Queue *pQ);

int PrintEntireQueue(Queue *pQ);

int GetServiceTime(Queue *pQ);