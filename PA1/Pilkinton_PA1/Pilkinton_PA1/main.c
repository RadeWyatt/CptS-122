/************************************************************************
NAME: RADE PILKINTON
CLASS: CPTS 122 FALL 2017
DATE: 9/6/17
ASSIGNMENT: PA1
DESCRIPTION: This program reads fitbit data from a csv file and determines user statistics based upon the data in the file. Statistics are then exported to another csv file.


*NOTICE* IF THIS DOES NOT COMPILE ITS BECAUSE IT WAS BUILT ON VISUAL STUDIO 2017. IF SO, EMAIL ME SO I CAN COPY IT OVER TO VS 2015 AND RESUBMIT
************************************************************************/
#include "header.h"


int main(void)
{
	FILE *infile = NULL, *outfile = NULL;
	infile = fopen("FitbitData.csv", "r");    //opens file for mode read
	outfile = fopen("Results.csv", "w");		//opens file for mode write

	FitbitData data[1440];

	char copyline[100] = "", minutes[9], line[100] = "", clearline[100] = "";
	double totcal = 0.0, totmiles = 0.0, avgheart = 0.0;
	int totfloors = 0, totsteps = 0, moststeps = 0, rangestart = 0, rangeend = 0;


	if (infile != NULL)																	 //Checks for file open success
	{
		
		fgets(line, 100, infile);														 //Gets first(title) line. Gets it out of the way.

		int j = 0;
		for (int k = 0; k < 1440; k++)													//Loop traverses the entire data set.
		{
			fgets(line, 100, infile);
			strcpy(copyline, line);
			newline(copyline, &clearline);
			int i = 0;
			char *parsed[100];
			for (char *token = strtok(clearline, ","); token != NULL; token = strtok(NULL, ",")) {                   //Tokenizes the line.
				parsed[i] = strdup(token);
				i++;
			}
			
			strcpy(data[j].minute, parsed[0]);
			
			data[j].calories = strtodub(parsed[1]);
			
			data[j].distance = strtodub(parsed[2]);
			
			data[j].floors = strtointeger(parsed[3]);
			
			data[j].heartRate = strtointeger(parsed[4]);
			
			data[j].steps = strtointeger(parsed[5]);
			
			data[j].sleeplevel = strtointeger(parsed[6]);
		
			j++;
			
		}

		computetotals(data, &totcal, &totmiles, &totfloors, &totsteps);						
		computeavgheart(data, &avgheart);											
		moststeps = maxsteps(data);
		findrange(data, &rangestart, &rangeend);


		fprintf(outfile, "Total Calories, Total Distance, Total Floors, Total Steps, Avg Heartrate, Max Steps, Sleep\n");
		fprintf(outfile, "%.9f, %.9f, %d, %d, %.2f, %d, %s:%s\n", totcal, totmiles, totfloors, totsteps, avgheart, data[moststeps].steps, data[rangestart].minute, data[rangeend].minute);

		printf("Total Calories, Total Distance, Total Floors, Total Steps, Avg Heartrate, Max Steps, Sleep\n");
		printf("%.9f, %.9f, %d, %d, %.2f, %d, %s:%s\n", totcal, totmiles, totfloors, totsteps, avgheart, data[moststeps].steps, data[rangestart].minute, data[rangeend].minute);

	}

	fclose(infile); //close infile
	fclose(outfile); //close outfile


	return 0;
}