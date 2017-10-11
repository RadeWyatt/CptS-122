/************************************************************************
NAME: RADE PILKINTON
CLASS: CPTS 122 FALL 2017
DATE: 9/6/17
ASSIGNMENT: PA1
DESCRIPTION: This program reads fitbit data from a csv file and determines user statistics based upon the data in the file. Statistics are then exported to another csv file.
************************************************************************/
#include "header.h"

/*
NAME: newline()
DESCRIPTION: This function looks for back to back commas based on ascii values. If they are found, a -1 character is placed between them to signify an empty data slot.
DATE:9/6/17
PARAMETERS: copyline and clearline
*/
void newline(char copyline[], char *clearline)
{
	char *mychar = "-1";
	char arr[100] = "";
	int x = 0;
	for (int i = 0; i < strlen(copyline); i++)
	{
		if (((int)copyline[i] == 44 && (int)copyline[i + 1] == 44))
		{
			x = i + 1;
		}
	}
	if (x != 0) {
		strncpy(arr, copyline, x);
		arr[x] = '\0';
		strcat(arr, mychar);
		strcat(arr, copyline + x);
		strcpy(clearline, arr);
	}
	else {
		strcpy(clearline, copyline);
	}
}


/*
NAME: strtodub()
DESCRIPTION: This function converts a character to a double.
DATE: 9/6/17
PARAMETERS: a character
*/
double strtodub(char* string[])
{	
	double num;
	
	num = atof(string);
	

	return num;
}

/*
NAME: strtointeger()
DESCRIPTION: This function converts a char to an int
DATE: 9/6/17
PARAMETERS: a character
*/
int strtointeger(char* string[])
{
	int num;
	
	num = atoi(string);
	
	return num;
}

/*
NAME: computetotals()
DESCRIPTION: This function computes the accumulative totals for some of the data
DATE: 9/6/17
PARAMETERS: Struct data, then pointers to store totals for the data
*/
void computetotals(FitbitData data[], double *totcal, double *totmiles, int *totfloors, int *totsteps)
{
	*totcal = 0, *totmiles = 0, *totfloors = 0, *totsteps = 0;
	for (int i = 0; i < 1440; i++)
	{
		if (data[i].calories != -1) {
			*totcal += data[i].calories;
		}
		if (data[i].distance != -1) {
			*totmiles += data[i].distance;
		}
		if (data[i].floors != -1) {
			*totfloors += data[i].floors;
		}
		if (data[i].steps != -1) {
			*totsteps += data[i].steps;
		}
	}
}

/*
NAME: computeavgheart()
DESCRIPTION: computes the average heart rate
DATE: 9/6/17
PARAMETERS: struct data, pointer to store avg heart rate
*/
void computeavgheart(FitbitData data[], double *avgheart)
{
	*avgheart = 0;
	int count = 1440;
	for (int i = 0; i < 1440; i++) {
		if (data[i].heartRate != -1) {
			*avgheart += data[i].heartRate;
		}
		else {
			count--;
		}
	}
	*avgheart = (*avgheart / count);
}

/*
NAME: maxsteps()
DESCRIPTION: determines max steps taken in one minute
DATE: 9/6/17
PARAMETERS: struct data
*/
int maxsteps(FitbitData data[])
{
	int max = 0, x = 0;
	for (int i = 0; i < 1440; i++) {
		if (data[i].steps >= max)
		{
			max = data[i].steps;
			x = i;
		}
	}
	return x;
}

/*
NAME: findrange()
DESCRIPTION: finds worst range of sleep during the day
DATE: 9/6/17
PARAMETERS: struct data, pointers to store beginning of range and end of range.
*/
void findrange(FitbitData data[], int *rangestart, int *rangeend)
{
	int sum = 0;
	for (int i = 0; i < 1440; i++) //traverses through each minute
	{
		if (data[i].sleeplevel > 1)   //If sleep is bad
		{
			int tempsum = 0, tempstart = 0, tempend = 0;
			tempstart = i;
			tempsum += data[i].sleeplevel;

			int j = i;
			while (data[j + 1].sleeplevel > 1) //while the next sleep is bad too
			{
				tempsum += data[j + 1].sleeplevel;

				if (data[j + 2].sleeplevel < 2) //If the next sleep is good quit
				{
					tempend = j + 1;
				}
				j++;
			}
			if (tempsum > sum) //if the sum is greater than our previous greatest range
			{
				sum = tempsum;
				*rangestart = tempstart;
				*rangeend = tempend;
			}
		}
	}
}
