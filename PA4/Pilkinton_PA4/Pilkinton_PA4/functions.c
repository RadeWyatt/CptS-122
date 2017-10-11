/************************************************************************
NAME: RADE PILKINTON
CLASS: CPTS 122 FALL 2017
DATE: 10/04/17
ASSIGNMENT: PA4
DESCRIPTION: This program simulates a grocery store with an express line and normal line. This is the functions file.
************************************************************************/
#include "header.h"


/*
This function creates a new Queuenode for a customer. It allocates memory on the heap for the queuenode, and also the data within the QueueNode.
*/ 
QueueNode *makeNode(Data newItem)
{
	QueueNode *pMem = (QueueNode *)malloc(sizeof(QueueNode));

	if (pMem != NULL)
	{
		pMem->pNext = NULL;
		pMem->pData = (Data *)malloc(sizeof(Data));

		if (pMem->pData != NULL)
		{
			*pMem->pData = newItem;
		}
		else
		{
			free(pMem);
		}
	}
	return pMem;
}

/*
This Function creates a new grocerynode for our linked list of groceries (BONUS). It selects a random item to be placed within the nodes data. 
*/
GroceryNode *makeGNode()
{
	char grocerylist[13][10] = { "Bacon", "Milk", "Cheese", "Cereal", "Flour", "Sugar", "Candy", "Juice", "Carrots", "Lettuce", "Tomatoes", "Potatoes", "Pepperoni"};
	GroceryNode *pTemp = (GroceryNode *)malloc(sizeof(GroceryNode));
	pTemp->NextItem = NULL;
	int randind;
	if (pTemp != NULL)
	{
		randind = rand() % 12;
		strcpy(pTemp->groceries, grocerylist[randind]);
	}
	return pTemp;
}

/*
This function enqueues, or adds, a queuenode to the end of the queue. It also generates a random amount of GroceryNodes and links them together within the QueueNode.
*/
int enqueue(Queue *pQ, Data newItem)
{
	QueueNode *pMem = makeNode(newItem);
	pMem->gNext = NULL;
	int success = 0, count = 0;

	if (pMem != NULL) // memory was successfully allocated
	{
		if (pQ->pFront == NULL) // empty?
		{
			// it's an empty queue!
			// connect both the head and tail to the one new node
			pQ->pFront = pQ->pRear = pMem;
			success = 1;
		}
		else // not empty
		{
			pQ->pRear->pNext = pMem;
			pQ->pRear = pMem;
			pQ->pRear->pNext = NULL;
			success = 1;
		}
	}
	while (count <= (pMem->pData->serviceTime))
	{
		GroceryNode *temp = NULL;
		temp = makeGNode();
		temp->NextItem = pMem->gNext;
		pMem->gNext = temp;
		temp = temp->NextItem;
		count++;
	}
	return success;
}

/*
This function dequeues a customer, or Queuenode, from the front of the Queue. 
*/
int DeQueue(Queue *pQ)
{
	int success = 0;
	//If queue is empty return 0
	if (pQ->pFront == NULL)
	{
		return success;
	}

	//Store previous front node and move front one node ahead
	QueueNode *temp = pQ->pFront;
	pQ->pFront = pQ->pFront->pNext;
	success = 1;

	//If front becomes NULL, then change rear to NULL as well
	if (pQ->pFront == NULL)
	{
		pQ->pRear = NULL;
	}
	free(temp);
	return success;
}

/*
 A utility function to create an empty queue
 */
struct Queue *CreateQueue()
{
	Queue *q = (Queue*)malloc(sizeof(Queue));
	q->pFront = q->pRear = NULL;
	return q;
}

/*
This function prints a either the Front or Rear Node of a Queue and displays information about that Node. 
*/
void PrintQueue(Queue *pQ, int WhichLine, int StartOrEnd, int ArrivalTime)
{
	// 1 = Express Line     2 = Normal Line
	// 1 = Start of Line    2 = End of Line
	if (!isEmpty(pQ))
	{
		if (WhichLine == 1)
		{
			if (StartOrEnd == 1)
			{
				printf("Customer #%d arrived in the Express Line at %d min\n", pQ->pRear->pData->customerNumber, ArrivalTime);
				printf("	Groceries: ");
				PrintGroceries(pQ);
				printf("\n\n");
			}
			else if (StartOrEnd == 2)
			{
				printf("Customer #%d departed the Express Line at %d min after a total of %d min in the line.\n\n", pQ->pFront->pData->customerNumber, ArrivalTime, pQ->pFront->pData->totalTime);
			}
		}
		else
		{
			if (StartOrEnd == 1)
			{
				printf("Customer #%d arrived in the Normal Line at %d min\n", pQ->pRear->pData->customerNumber, ArrivalTime);
				printf("	Groceries: ");
				PrintGroceries(pQ);
				printf("\n\n");
			}

			else if (StartOrEnd == 2)
			{
				printf("Customer #%d departed the Normal Line at %d min after a total of %d min in the line.\n\n", pQ->pFront->pData->customerNumber, ArrivalTime, pQ->pFront->pData->totalTime);
			}
		}
	}
	else
	{
		printf("The Line is empty!");
	}
}

/*
A function to get N minutes from the user for main game loop.
*/
int getN()
{
	int n = 0;
	printf("Welcome to the Grocery Store Simulator!\n\nHow many minutes shall the simulator run for?\n\nSelection: ");
	scanf("%d", &n);
	system("cls");
	return n;
}

/*
A function to determine whether the Queue is empty. Checks front Node for NULL.
*/
int isEmpty(Queue *pQ)
{
	if (pQ->pFront == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
Prints the Groceries in the linked list in a Queuenode. It is called when the customer is enqueued. 
*/
void PrintGroceries(Queue *pQ)
{
	GroceryNode *temp = pQ->pFront->gNext;
	while (temp->NextItem != NULL)
	{
		printf("%s ", temp->groceries);
		temp = temp->NextItem;
	}
}
 /*
 Prints the entire Queue state. It is called after every 10 minutes in the simulation. 
 */
int PrintEntireQueue(Queue *pQ)
{
	QueueNode *temp = NULL;
	temp = pQ->pFront;

	if (isEmpty(pQ))
	{
		printf("The line is empty\n");
		return 0;
	}
	while (temp != NULL)
	{
		printf("Customer #%d with a total service time of %d min\n", temp->pData->customerNumber, temp->pData->totalTime);
		temp = temp->pNext;
	}
}

/*
Utility function to get total service time for a particular customer.
*/
int GetServiceTime(Queue *pQ)
{
	int servicetime = 0;
	QueueNode *temp = NULL;
	temp = pQ->pFront;
	if (isEmpty(pQ))
	{
		return servicetime;
	}
	while (temp != NULL)
	{
		servicetime += temp->pData->serviceTime;
		temp = temp->pNext;
	}
	return servicetime;
}