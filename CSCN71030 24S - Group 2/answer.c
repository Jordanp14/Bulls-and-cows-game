#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// get the difficulty level from the command line
int readDifficulty(char* difficulty)
{
	// convert all of the chars in the command line to capitals
	for (int i = 0; i < strlen(difficulty); i++)
	{
		difficulty[i] = toupper(difficulty[i]);
	}

	int difLength = 0;

	// compare the strings and if it returns 0 then that difficulty was selected
	if (strncmp(difficulty, "EASY", strlen(difficulty)) == 0)
		difLength = 4;
	else if (strncmp(difficulty, "MEDIUM", strlen(difficulty)) == 0)
		difLength = 5;
	else if (strncmp(difficulty, "HARD", strlen(difficulty)) == 0)
		difLength = 6;
	else
	{
		printf("invalid command argument. Accepted arguments are \"easy\", \"medium\", or \"hard\"\n");
	}

	return difLength;
}

// randomly generates a dynamically allocated integer array
int* getRandomInt(int length)
{
	// allocate the memory for the array based on the length generated from the difficulty
	int* num = (int*)malloc(length * sizeof(int));
	// check that memory was successfully allocated
	if (num == NULL)
	{
		printf("Could not allocate memory\t exiting...");
		exit(1);
	}

	// generate numbers from 0-9 based on the difficulty length
	for (int i = 0; i < length; i++)
	{
		num[i] = (rand() % 10);
	}
	return num;
}
// print the int* answer
void printAnswer(int* answer, int difLength)
{
	for (int i = 0; i < difLength; i++)
	{
		printf("%d", answer[i]);
	}
}