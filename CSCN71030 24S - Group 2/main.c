//CSCN71030 Group 2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "LeaderboardSave.h"
#include "answer.h"

int main(int argc, char* argv[])
{
	// seed the random
	srand(time(NULL));

	int difLength = readDifficulty(argv[1]);
	int* answer = getRandomInt(difLength);

	printAnswer(answer, difLength);
}
