/************************************************************************
NAME: RADE PILKINTON
CLASS: CPTS 122 FALL 2017
DATE: 9/10/17
ASSIGNMENT: PA2
DESCRIPTION: This program manipulates a music collection. This is the function file.
************************************************************************/
#include "header.h"

/*
NAME: mainmenu()
DESCRIPTION: This function displays menu options and accepts user input for their choice of option.
DATE CREATED :9/10/17
DATE LAST MODIFIED: 9/10/17
PARAMETERS: none
PRECONDITION:
POSTCONDITION:
*/
int menu()
{
	int choice;
	printf("(1) LOAD\n(2) STORE\n(3) DISPLAY\n(4) INSERT\n(5) DELETE\n(6) EDIT\n(7) SORT\n(8) RATE\n(9) PLAY\n(10) SHUFFLE\n(11) EXIT\n\n\n");
	printf("Select your option:  ");
	scanf("%d", &choice);
	system("cls");
	return choice;
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
NAME: makenode()
DESCRIPTION: This function allocated memory on the heap for a node.
DATE CREATED :9/10/17
DATE LAST MODIFIED: 9/10/17
PARAMETERS: Record type newrecord
PRECONDITION:
POSTCONDITION:
*/
Node *makenode(Record *newrecord)
{
	Node *pMem = NULL;
	pMem = (Node *) malloc(sizeof(Node)); //Allocating space on the heap
	if (pMem != NULL) //malloc succeeded
	{
		pMem->pNext = NULL;
		pMem->pPrev = NULL;
		pMem->data = *newrecord;
	}
}


/*
NAME: insertfront()
DESCRIPTION: This function inserts new nodes at the front of our music collection.
DATE CREATED: 9/10/17
DATE LAST MODIFIED: 9/10/17
PARAMETERS: Our Music Collection, Record type newrecord
PRECONDITION:
POSTCONDITION:
*/
int insertfront(Node **pDMM, Record *newrecord)
{
	Node *pMem = NULL;
	int success = 0;
	pMem = makenode(newrecord);
	//Did malloc () fail? Null ptr
	if (pMem != NULL) {
		success = 1;
		pMem->pNext = NULL;
		pMem->data = *newrecord;
		if (*pDMM == NULL) //Dealing with an empty list!
		{
			(*pDMM) = pMem;
		}
		else //Not dealing with empty list
		{
			pMem->pNext = *pDMM;
			(*pDMM)->pPrev = pMem;
			*pDMM = pMem;
		}
	}
	return success;
}

/*
NAME: printList()
DESCRIPTION: This function prints out music collection.
DATE CREATED :9/10/17
DATE LAST MODIFIED: 9/10/17
PARAMETERS: Our music collection.
PRECONDITION:
POSTCONDITION:
*/
void printList(Node *pDMM) 
{
	int selection;
	do
	{
		printf("(1) Print All Records\n(2) Print All Records For an Artist\nSelect an Option: ");
		scanf("%d", &selection);
		system("cls");
	} while (selection < 1 || selection >2);
	switch (selection)
	{
	case 1:
		if (pDMM == NULL)
		{
			printf("Music Collection is empty\n");
		}
		else {
			Node *tempnode = NULL;
			tempnode = (Node *)malloc(sizeof(Node));
			tempnode = pDMM;
			int end = 0;
			while (end == 0) 
			{
				printf("Artist: %s\n", tempnode->data.artist);
				printf("Album: %s\n", tempnode->data.album);
				printf("Song: %s\n", tempnode->data.songtitle);
				printf("Genre: %s\n", tempnode->data.genre);
				printf("Length: %d:%d\n", tempnode->data.songlength.minutes, tempnode->data.songlength.seconds);
				printf("Times Played: %d\n", tempnode->data.timesplayed);
				printf("Rating: %d\n", tempnode->data.rating);
				printf("\n\n");
				if (tempnode->pNext != NULL)
				{
					tempnode = tempnode->pNext;
				}
				else {
					end = 1;
				}
			}
		}
		break;
	case 2:
		if (pDMM == NULL)
		{
			printf("Music Collection is empty\n");
		}
		else {
			Node *tempnode = NULL;
			char artist[30];
			tempnode = (Node *)malloc(sizeof(Node));
			tempnode = pDMM;
			int end = 0;
			printf("Enter the name of the desired artist as it appears in the music collection: ");
			scanf("%c");
			gets(artist, 100, stdin);
			system("cls");
			while (end == 0) 
			{
				if (strcmp(artist, tempnode->data.artist) == 0)
				{
					printf("Artist: %s\n", tempnode->data.artist);
					printf("Album: %s\n", tempnode->data.album);
					printf("Song: %s\n", tempnode->data.songtitle);
					printf("Genre: %s\n", tempnode->data.genre);
					printf("Length: %d:%d\n", tempnode->data.songlength.minutes, tempnode->data.songlength.seconds);
					printf("Times Played: %d\n", tempnode->data.timesplayed);
					printf("Rating: %d\n", tempnode->data.rating);
					printf("\n\n");
				}
				if (tempnode->pNext != NULL)
				{
					tempnode = tempnode->pNext;
				}
				else {
					end = 1;
				}
			}
		}
		break;
	}
}


/*
NAME: readrecords()
DESCRIPTION: This function reads a line and puts it in a record.
DATE CREATED :9/10/17
DATE LAST MODIFIED: 9/10/17
PARAMETERS: infile
PRECONDITION:
POSTCONDITION:
*/
void readrecords(FILE *infile, Node ***pDMM)
{
	if (infile != NULL)
	{
		while (!feof(infile))
		{
			char line[100] = "", copyline[100] = "";
			Record myrecord = {"","","","",0,0,0,0};
			fgets(line, 100, infile);
			strcpy(copyline, line);
			int i = 0;
			char *parsed[100] = { "" };
			char temp[100];
			if ((int)line[0] == 34) //If the artist name is separated by quotes, first token delimeter is quote mark.
			{

				for (char *token = strtok(copyline, "\""); token != NULL; token = strtok(NULL, ",:")) {
					parsed[i] = strdup(token);
					i++;
				}

				strcpy(myrecord.artist, parsed[0]);
				strcpy(myrecord.album, parsed[1]);
				strcpy(myrecord.songtitle, parsed[2]);
				strcpy(myrecord.genre, parsed[3]);
				myrecord.songlength.minutes = strtointeger(parsed[4]);
				myrecord.songlength.seconds = strtointeger(parsed[5]);
				myrecord.timesplayed = strtointeger(parsed[6]);
				myrecord.rating = strtointeger(parsed[7]);
			
			}
			else //Otherwise tokenize by commas
			{
				for (char *token = strtok(copyline, ",:"); token != NULL; token = strtok(NULL, ",:")) {
					parsed[i] = strdup(token);
					i++;
				}
				strcpy(myrecord.artist, parsed[0]);
				strcpy(myrecord.album, parsed[1]);
				strcpy(myrecord.songtitle, parsed[2]);
				strcpy(myrecord.genre, parsed[3]);
				myrecord.songlength.minutes = strtointeger(parsed[4]);
				myrecord.songlength.seconds = strtointeger(parsed[5]);
				myrecord.timesplayed = strtointeger(parsed[6]);
				myrecord.rating = strtointeger(parsed[7]);
			
			}
			insertfront(pDMM, &myrecord);
		}
	}
}

/*
NAME: pleasecontinue()
DESCRIPTION: Continue function xD
DATE CREATED :9/10/17
DATE LAST MODIFIED: 9/10/17
PARAMETERS: 
PRECONDITION:
POSTCONDITION:
*/
void pleasecontinue()
{
	printf("Press any key to continue........\n");
	getch();
	system("cls");
}

/*
NAME: iscomma()
DESCRIPTION: Checks for a comma in the string
DATE CREATED :9/10/17
DATE LAST MODIFIED: 9/10/17
PARAMETERS: one string
PRECONDITION:
POSTCONDITION:
*/
int iscomma(char string[])
{
	int found = 0;
	for (int i = 0; i < strlen(string); i++)
	{
		if ((int)string[i] == 44)
		{
			found = 1;
		}
	}
	return found;
}


/*
NAME: storerecords()
DESCRIPTION: Stores the records into the csv file.
DATE CREATED :9/10/17
DATE LAST MODIFIED: 9/10/17
PARAMETERS: outfile, music records
PRECONDITION:
POSTCONDITION:
*/
void storerecords(FILE *outfile, Node **pDMM)
{
	int end = 0;
	Node *tempnode = (Node *)malloc(sizeof(Node));
	tempnode = pDMM;
	while (end == 0)
	{
		if (tempnode->pNext != NULL)
		{
			if (iscomma(tempnode->data.artist)) {
				fprintf(outfile, "\"%s\",%s,%s,%s,%d:%d,%d,%d\n", tempnode->data.artist, tempnode->data.album, tempnode->data.songtitle, tempnode->data.genre, tempnode->data.songlength.minutes, tempnode->data.songlength.seconds, tempnode->data.timesplayed, tempnode->data.rating);
			}
			else {
				fprintf(outfile, "%s,%s,%s,%s,%d:%d,%d,%d\n", tempnode->data.artist, tempnode->data.album, tempnode->data.songtitle, tempnode->data.genre, tempnode->data.songlength.minutes, tempnode->data.songlength.seconds, tempnode->data.timesplayed, tempnode->data.rating);
			}
		
			tempnode = tempnode->pNext;
		}
		else {
			if (iscomma(tempnode->data.artist)) {
				fprintf(outfile, "\"%s\",%s,%s,%s,%d:%d,%d,%d", tempnode->data.artist, tempnode->data.album, tempnode->data.songtitle, tempnode->data.genre, tempnode->data.songlength.minutes, tempnode->data.songlength.seconds, tempnode->data.timesplayed, tempnode->data.rating);
			}
			else {
				fprintf(outfile, "%s,%s,%s,%s,%d:%d,%d,%d", tempnode->data.artist, tempnode->data.album, tempnode->data.songtitle, tempnode->data.genre, tempnode->data.songlength.minutes, tempnode->data.songlength.seconds, tempnode->data.timesplayed, tempnode->data.rating);
			}
			end = 1;
		}
	}
}

/*
NAME: editrecords()
DESCRIPTION: Allows the user to edit records in the music database
DATE CREATED :9/10/17
DATE LAST MODIFIED: 9/10/17
PARAMETERS: DMM
PRECONDITION:
POSTCONDITION:
*/
void editrecords(Node **pDMM)
{
	char editname[30] = "", temp;
	printf("Enter the name of the artist: ");
	scanf("%c", &temp);
	gets(editname, 100, stdin);
	printf("\n\n");
	int end = 0, count = 0;
	Node *tempnode = (Node *)malloc(sizeof(Node));
	tempnode = *pDMM;
	 
	printf("Records by %s:\n\n", &editname);
	while (end == 0)
	{
		if (strcmp(editname, tempnode->data.artist) == 0)
		{
			printf("Artist: %s\n", tempnode->data.artist);
			printf("Album: %s\n", tempnode->data.album);
			printf("Song: %s\n", tempnode->data.songtitle);
			printf("Genre: %s\n", tempnode->data.genre);
			printf("Length: %d:%d\n", tempnode->data.songlength.minutes, tempnode->data.songlength.seconds);
			printf("Times Played: %d\n", tempnode->data.timesplayed);
			printf("Rating: %d\n", tempnode->data.rating);
			printf("\n\n");
			count++;
		}
		if (tempnode->pNext != NULL)
		{
			tempnode = tempnode->pNext;
		}
		else
		{
			end = 1;
		}
	}
	
	if (count == 1)
	{
		printf("Press any key to edit this record....\n");
		getch();
		system("cls");
		end = 0;
		char temp;
		tempnode = *pDMM;
		while (end == 0)
		{
			if (strcmp(editname, tempnode->data.artist) == 0)
			{
				puts("Enter Artist: ");
				scanf("%s", &tempnode->data.artist);
				puts("Enter Album: ");
				scanf("%s", &tempnode->data.album);
				puts("Enter Song Title: ");
				scanf("%s", &tempnode->data.songtitle);
				puts("Enter Genre: ");
				scanf("%s", &tempnode->data.genre);
				puts("Enter Song Length: ");
				scanf("%d%c%d", &tempnode->data.songlength.minutes, &temp, &tempnode->data.songlength.seconds);
				puts("Enter Times Played: ");
				scanf("%d", &tempnode->data.timesplayed);
				puts("Enter Rating: ");
				scanf("%d", &tempnode->data.rating);
			}
			if (tempnode->pNext != NULL)
			{
				tempnode = tempnode->pNext;
			}
			else
			{
				end = 1;
			}
		}
	}
	else 
	{
		char tempsong[30] = "";
		printf("Enter the name of the song to be edited: ");
		gets(tempsong, 100, stdin);
		printf("Press any key to edit this record....\n");
		getch();
		system("cls");
		end = 0;
		char temp;
		tempnode = *pDMM;
		while (end == 0)
		{
			if (strcmp(tempsong, tempnode->data.songtitle) == 0)
			{
				puts("Enter Artist: ");
				scanf("%s", &tempnode->data.artist);
				puts("Enter Album: ");
				scanf("%s", &tempnode->data.album);
				puts("Enter Song Title: ");
				scanf("%s", &tempnode->data.songtitle);
				puts("Enter Genre: ");
				scanf("%s", &tempnode->data.genre);
				puts("Enter Song Length: ");
				scanf("%d%c%d", &tempnode->data.songlength.minutes, &temp, &tempnode->data.songlength.seconds);
				puts("Enter Times Played: ");
				scanf("%d", &tempnode->data.timesplayed);
				puts("Enter Rating: ");
				scanf("%d", &tempnode->data.rating);
			}
			if (tempnode->pNext != NULL)
			{
				tempnode = tempnode->pNext;
			}
			else
			{
				end = 1;
			}
		}
	}
}


/*
NAME: ratesong()
DESCRIPTION: allows a user to rate a song
DATE CREATED :9/10/17
DATE LAST MODIFIED: 9/10/17
PARAMETERS: DMM
PRECONDITION:
POSTCONDITION:
*/
void ratesong(Node **pDMM)
{
	char songtorate[30] = "", temp;
	printf("Enter the name of the song to rate: ");
	scanf("%c", &temp);
	gets(songtorate, 100, stdin);
	printf("\n\n");
	int end = 0;
	Node *tempnode = (Node *)malloc(sizeof(Node));
	tempnode = *pDMM;

	while (end == 0)
	{
		if (strcmp(songtorate, tempnode->data.songtitle) == 0)
		{
			int rating;
			printf("Enter Rating (1-5): ");
			scanf("%d", &rating);
			tempnode->data.rating = rating;
		}
		if (tempnode->pNext != NULL)
		{
			tempnode = tempnode->pNext;
		}
		else
		{
			end = 1;
		}
	}
}

/*
NAME: playsongs()
DESCRIPTION: Allows user to play songs
DATE CREATED :9/10/17
DATE LAST MODIFIED: 9/10/17
PARAMETERS: DMM
PRECONDITION:
POSTCONDITION:
*/
void playsongs(Node **pDMM)
{
	int end = 0;
	Node *tempnode = (Node *)malloc(sizeof(Node));
	tempnode = *pDMM;

	while (end == 0)
	{
		printf("Playing %s - %s", tempnode->data.songtitle, tempnode->data.artist);
		_sleep(5000);
		system("cls");

		if (tempnode->pNext != NULL)
		{
			tempnode = tempnode->pNext;
		}
		else
		{
			end = 1;
		}
	}

}