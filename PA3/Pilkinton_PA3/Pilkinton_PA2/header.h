/************************************************************************
NAME: RADE PILKINTON
CLASS: CPTS 122 FALL 2017
DATE: 9/22/17
ASSIGNMENT: PA3
DESCRIPTION: This program manipulates a music collection. This is the header file.
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct duration
{
	int minutes;
	int seconds;
} Duration;

typedef struct record
{
	char artist[30];
	char album[30];
	char songtitle[30];
	char genre[30];
	Duration songlength;
	int timesplayed;
	int rating;
} Record;

typedef struct node
{
	Record data;
	struct node* pNext;
	struct node* pPrev;
} Node;

Node *makenode(Record *newrecord);

int strtointeger(char* string[]);

int insertfront(Node **pDMM, Record *newrecord);

void readrecords(FILE *infile, Node ***pDMM);

void printList(Node *pDMM);

int menu();

void pleasecontinue();

void storerecords(FILE *outfile, Node **pDMM);

int iscomma(char string[]);

void editrecords(Node **pDMM);

void ratesong(Node **pDMM);

void playsongs(Node **pDMM);

void insertatfront(Node **pDMM);

void deletenode(Node **pDMM);

void sort(Node **pDMM);

void swap(Node *a, Node *b);

void shuffle(Node **pDMM);