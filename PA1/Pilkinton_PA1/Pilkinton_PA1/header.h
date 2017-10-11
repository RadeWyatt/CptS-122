/************************************************************************
NAME: RADE PILKINTON
CLASS: CPTS 122 FALL 2017
DATE: 9/6/17
ASSIGNMENT: PA1
DESCRIPTION: This program reads fitbit data from a csv file and determines user statistics based upon the data in the file. Statistics are then exported to another csv file.
************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum sleep
{
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;

typedef struct fitbit
{
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleeplevel;
} FitbitData;

void newline(char copyline[], char *clearline);
double strtodub(char* string[]);
int strtointeger(char* string[]);
void computetotals(FitbitData data[], double *totcal, double *totmiles, int *totfloors, int *totsteps);
void computeavgheart(FitbitData data[], double *avgheart);
int maxsteps(FitbitData data[]);
void findrange(FitbitData data[], int *rangestart, int *rangeend);