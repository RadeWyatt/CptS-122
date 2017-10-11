/************************************************************************
NAME: RADE PILKINTON
CLASS: CPTS 122 FALL 2017
DATE: 10/04/17
ASSIGNMENT: PA4
DESCRIPTION: This program simulates a grocery store with an express line and normal line. This is the main file.
************************************************************************/
#include "header.h"

int main(void)
{
	srand(time(NULL));
	Queue *ExpressLane = CreateQueue();
	Queue *NormalLane = CreateQueue();
	int n = 0, customernumber = 0, totaltime = 0, servicetime = 0, TimeInLine = 0, ExpressNum = 0, NormalNum = 0,
		expressserviced = 1, normalserviced = 1, GoalTimeNormal = 0, GoalTimeExpress = 0, servicetime2 = 0, TimeInLine2 = 0;

	n = getN(); //Gets N minutes to loop for

	while (totaltime <= n) //Main Game Loop
	{
		if (expressserviced) //If the last customer has arrived in line, generate a new one.
		{

			ExpressNum = rand() % 5 + 1;
			expressserviced = 0;
			GoalTimeExpress = ExpressNum + totaltime; //When the customer enters the line.
		}

		if (normalserviced)  //If the last customer has arrived in line, generate a new one.
		{

			NormalNum = rand() % 6 + 3;
			normalserviced = 0;
			GoalTimeNormal = NormalNum + totaltime;
		}


		if (GoalTimeExpress == totaltime) //If it is time for the new customer to join the line.
		{
			int itemnum = (rand() % 5) + 1; //How many grocery items
			customernumber++;
			TimeInLine = itemnum + GetServiceTime(ExpressLane);
			Data Ecustomer = { customernumber, itemnum, TimeInLine };
			enqueue(ExpressLane, Ecustomer);
			PrintQueue(ExpressLane, 1, 1, GoalTimeExpress);
			expressserviced = 1;

		}

		if (GoalTimeNormal == totaltime)  //If it is time for the new customer to join the line.
		{
			customernumber++;
			int itemnum2 = (rand() % 5) + 1; //How many grocery items
			TimeInLine2 =  itemnum2 + GetServiceTime(NormalLane);
			Data Ncustomer = { customernumber, itemnum2, TimeInLine2 };
			enqueue(NormalLane, Ncustomer);
			PrintQueue(NormalLane, 2, 1, GoalTimeNormal);
			normalserviced = 1;
		}
	
		if (!isEmpty(ExpressLane)) //If Queue is not empty
		{
			if (ExpressLane->pFront->pData->serviceTime == 0) //If customer is to be dequeued
			{
				PrintQueue(ExpressLane, 1, 2, totaltime);
				DeQueue(ExpressLane);
			}
		}
		if (!isEmpty(NormalLane))
		{
			if (NormalLane->pFront->pData->serviceTime == 0)
			{
				PrintQueue(NormalLane, 2, 2, totaltime);
				DeQueue(NormalLane);
			}
		}

		if (totaltime % 10 == 0 && totaltime != 0) //Prints at 10 minute intervals
		{
			printf("\n\n\nCurrent State of Express Line at %d minutes\n------------------------------------\n", totaltime);
			PrintEntireQueue(ExpressLane);
			printf("\n------------------------------------\n\n");

			printf("\n\nCurrent State of Normal Line at %d minutes\n------------------------------------\n", totaltime);
			PrintEntireQueue(NormalLane);
			printf("\n------------------------------------\n\n\n");
		}

		if (n == 1440) // 24 Hours has gone by
		{
			customernumber = 0;
		}

		if (!isEmpty(ExpressLane))
		{
			ExpressLane->pFront->pData->serviceTime -= 1;
		}
		if (!isEmpty(NormalLane))
		{
			NormalLane->pFront->pData->serviceTime -= 1;
		}
		totaltime++;
	}

	return 0;
}