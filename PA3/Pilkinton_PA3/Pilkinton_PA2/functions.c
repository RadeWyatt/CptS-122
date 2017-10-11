/************************************************************************
NAME: RADE PILKINTON
CLASS: CPTS 122 FALL 2017
DATE: 9/22/17
ASSIGNMENT: PA3
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
	char editname[30] = "";
	printf("Enter the name of the artist: ");
	scanf("%c");
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
	char songtorate[30] = "";
	printf("Enter the name of the song to rate: ");
	scanf("%c");
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


/*
NAME: insertatfront()
DESCRIPTION: Inserts new record at the front of the list
DATE CREATED :9/10/17
DATE LAST MODIFIED: 9/10/17
PARAMETERS: DMM
PRECONDITION:
POSTCONDITION:
*/
void insertatfront(Node **pDMM)
{
	
	Node *pMem = NULL;
	Record newrecord;
	char temp;
	printf("Enter Artist Name: ");
	scanf("%c", &temp);
	gets(newrecord.artist, 100, stdin);
	putch('\n');
	printf("Enter Album: ");
	gets(newrecord.album, 100, stdin);
	putch('\n');
	printf("Enter Song Title: ");
	gets(newrecord.songtitle, 100, stdin);
	putch('\n');
	printf("Enter Genre: ");
	gets(newrecord.genre, 100, stdin);
	putch('\n');
	printf("Enter Song Length: ");
	scanf("%d%c%d", &newrecord.songlength.minutes, &temp, &newrecord.songlength.seconds);
	putch('\n');
	printf("Enter Times Played: ");
	scanf("%d", &newrecord.timesplayed);
	putch('\n');
	printf("Enter Song Rating: ");
	scanf("%d", &newrecord.rating);
	putch('\n');
	insertfront(pDMM, &newrecord);
}

/*
NAME: deletenode()
DESCRIPTION: deletes a specified node
DATE CREATED :9/10/17
DATE LAST MODIFIED: 9/10/17
PARAMETERS: DMM
PRECONDITION:
POSTCONDITION:
*/
void deletenode(Node **pDMM)
{
	char song[30], tempchar;
	Node *temp = (Node *)malloc(sizeof(Node));
	Node *pBack = NULL;
	Node *pCur = NULL;
	temp = *pDMM;
	pCur = temp;
	printf("Enter Name of Song to Delete: ");
	scanf("%c", &tempchar);
	gets(song, 100, stdin);

	if (temp == NULL)
	{
		return 0;
	}
	else
	{
		while (pCur->pNext != NULL && strcmp(song, pCur->data.songtitle) != 0)
		{
			pBack = pCur;
			pCur = pCur->pNext;
		}
		if (pBack == NULL)
		{
			temp = pCur;
			*pDMM = pCur->pNext;
			free(temp);
		}
		
		else if (pBack != NULL && strcmp(pCur->data.songtitle, song) == 0 && pCur->pNext != NULL)
		{
			temp = pCur;
			pCur->pPrev->pNext = pCur->pNext;
			pCur->pNext->pPrev = pCur->pPrev;
			free(temp);
		}
		else if (pCur->pNext == NULL)
		{
			temp = pCur;
			temp->pPrev->pNext = NULL;
			free(temp);
		}
	}

}

/*
NAME: sort()
DESCRIPTION: Allows user to sort list in a variety of ways
DATE CREATED :9/10/17
DATE LAST MODIFIED: 9/20/17
PARAMETERS: DMM
PRECONDITION:
POSTCONDITION:
*/
void sort(Node **pDMM)
{
	int selection = 0;
	printf("(1) Sort based on artist\n(2) Sort based on album title\n(3) Sort based on rating\n(4) Sort based on times played\n\nSelect your option: ");
	scanf("%d", &selection);
	printf("\n");
	int swapped, i;
	Node *ptr1 = (Node *)malloc(sizeof(Node));
	Node *lptr = NULL;
	switch (selection)
	{
	case 1:

		/* Checking for empty list */
		if (ptr1 == NULL)
			break;
		do
		{
			swapped = 0;
			ptr1 = *pDMM;
			while (ptr1->pNext != lptr)
			{
				if ((int)ptr1->data.artist[0] < (int)ptr1->pNext->data.artist[0])
				{
					swap(ptr1, ptr1->pNext);
					swapped = 1;
				}
				if ((int)ptr1->data.artist[0] == (int)ptr1->pNext->data.artist[0])
				{
					if ((int)ptr1->data.artist[1] < (int)ptr1->pNext->data.artist[1])
					{
						swap(ptr1, ptr1->pNext);
						swapped = 1;
					}
				}
				ptr1 = ptr1->pNext;
			}
			lptr = ptr1;
		} while (swapped);
		break;
	case 2:
		/* Checking for empty list */
		if (ptr1 == NULL)
			break;
		do
		{
			swapped = 0;
			ptr1 = *pDMM;
			while (ptr1->pNext != lptr)
			{
				if ((int)ptr1->data.album[0] < (int)ptr1->pNext->data.album[0])
				{
					swap(ptr1, ptr1->pNext);
					swapped = 1;
				}
				if ((int)ptr1->data.album[0] == (int)ptr1->pNext->data.album[0])
				{
					if ((int)ptr1->data.album[1] < (int)ptr1->pNext->data.album[1])
					{
						swap(ptr1, ptr1->pNext);
						swapped = 1;
					}
				}
				ptr1 = ptr1->pNext;
			}
			lptr = ptr1;
		} while (swapped);
		break;
	case 3:
		/* Checking for empty list */
		if (ptr1 == NULL)
			break;
		do
		{
			swapped = 0;
			ptr1 = *pDMM;
			while (ptr1->pNext != lptr)
			{
				if (ptr1->data.rating < ptr1->pNext->data.rating)
				{
					swap(ptr1, ptr1->pNext);
					swapped = 1;
				}
				ptr1 = ptr1->pNext;
			}
			lptr = ptr1;
		} while (swapped);
		break;
	case 4: 
		/* Checking for empty list */
		if (ptr1 == NULL)
			break;
		do
		{
			swapped = 0;
			ptr1 = *pDMM;
			while (ptr1->pNext != lptr)
			{
				if (ptr1->data.timesplayed < ptr1->pNext->data.timesplayed)
				{
					swap(ptr1, ptr1->pNext);
					swapped = 1;
				}
				ptr1 = ptr1->pNext;
			}
			lptr = ptr1;
		} while (swapped);
		break;
	}


}

/*
NAME: swap()
DESCRIPTION: Copies data of one node to another
DATE CREATED :9/20/17
DATE LAST MODIFIED: 9/20/17
PARAMETERS: DMM
PRECONDITION:
POSTCONDITION:
*/
void swap(Node *a, Node *b)
{
	Record temp = a->data;
	a->data = b->data;
	b->data = temp;
}

/*
NAME: swapints()
DESCRIPTION: Swaps values of one int to another
DATE CREATED :9/20/17
DATE LAST MODIFIED: 9/20/17
PARAMETERS: DMM
PRECONDITION:
POSTCONDITION:
*/
void swapints(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


/*
NAME: shuffle()
DESCRIPTION: Allows user to play suffles songs
DATE CREATED :9/20/17
DATE LAST MODIFIED: 9/20/17
PARAMETERS: DMM
PRECONDITION:
POSTCONDITION:
*/
void shuffle(Node **pDMM)
{
	int numsongs = 0, count = 0;

	Node *temp = (Node *)malloc(sizeof(Node));
	temp = *pDMM;
	 //Getting Number of nodes
	if (temp != NULL)
	{
		while (temp != NULL)
		{
			temp = temp->pNext;
			numsongs++;
		}
	}
	//Initializing Array of size numsongs
	int *arr = (int *)calloc(numsongs, sizeof(int));

	//Inserting order
	for (int i = 0; i < numsongs; i++)
	{
		arr[i] = i;
	}

	srand(time(NULL));

	for (int i = numsongs - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		swapints(&arr[i], &arr[j]);
	}
	
	temp = *pDMM;
	int position = 0, songsplayed = 0, p = 0;
	while (songsplayed != numsongs)
	{
		if (arr[p] > position)
		{
			while (position != arr[p])
			{
				temp = temp->pNext;
				position++;
			}
			printf("Playing %s by %s....", temp->data.songtitle, temp->data.artist);
			_sleep(2000);
			system("cls");
		}
		else if (arr[p] < position)
		{
			while (position != arr[p])
			{
				temp = temp->pPrev;
				position--;
			}
			printf("Playing %s by %s....", temp->data.songtitle, temp->data.artist);
			_sleep(2000);
			system("cls");
		}
		else
		{
			printf("Playing %s by %s....", temp->data.songtitle, temp->data.artist);
			_sleep(2000);
			system("cls");
		}
		songsplayed++;
		p++;
	}
	free(arr);
}