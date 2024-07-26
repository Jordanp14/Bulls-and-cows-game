//CSCN71030 Group 2
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "validate (correct p).h"
#include "LeaderboardSave.h"
#include "UserInterface.h"
#include "answer.h"
#include "validateWrongPosition.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Invalid command line format, difficulty must be entered");
		exit(1);
	}

	int  value, score = 0, bulls = 0, cows = 0, input;
	char username[10] = { 0 };
	char difficulty[7] = { 0 };
	char leaderboardDifficulty[7] = { 0 };
	bool continueGame = true;

	// seed the random
	srand(time(NULL));

	// read command line argument to get difficulty length
	int difLength = readDifficulty(argv[1]);

	//generate random int* for answer
	int* answer = getRandomInt(difLength);

	// temp for testing
	// print("%d", difLength);
	//printAnswer(answer, difLength);

	int* guess = (int*)malloc(difLength * sizeof(int));
	// check that memory was successfully allocated
	if (guess == NULL)
	{
		printf("Could not allocate memory\t exiting...");
		exit(1);
	}
	// add get username function 
	displayTitle();
	getUsername(username);

	// ask if user would like to reload previous game
	// might not be needed but im worried about bugs if difficulty is changed between games
	do {
		printf("Would you like to reload a previous game?\n1.Yes\n2.No\n");
		input = selectMenuOption();
	} while (input != 1 && input != 2);

	// reload prev game 
	if (input == 1)
	{
		Reload_Game_State(username, &score, guess, &difLength, difficulty);

	}

	// set command line argument to difficulty
	strncpy(difficulty, argv[1], strnlen(argv[1], 7));


	while (continueGame)
	{
		// game menu
		gameMenu();
		input = selectMenuOption();

		switch (input)
		{
		case 1:

			if (!Reload_Game_State(username, &score, guess, &difLength, difficulty))
				break;


		case 2:

			do
			{
				guess = getGuess(difLength, username);
				if (guess[0] == -1)
				{
					break;
				}

				//save game after each guess
				Save_Game_State(username, score, guess, difLength, difficulty);

				// add one to score
				score++;

				// validate guess
				bulls = validate_correct_position(guess, answer, difLength);
				cows = validate_wrong_position(guess, answer, difLength);

				//print results to user
				printf("There are %d bulls and %d cows.\n", bulls, cows);

			} while (bulls != difLength);
			break;

		case 3:
			do
			{
				printf("Which difficulty would you like to display?\n1. Easy\n2. Medium\n3. Hard\n");
				value = scanf("%s", leaderboardDifficulty);

			} while (value != 1 && readDifficulty(leaderboardDifficulty) != 4 ||
				readDifficulty(leaderboardDifficulty) != 5 || readDifficulty(leaderboardDifficulty) != 6);


			Display_Leaderboard(leaderboardDifficulty);
			break;
		case 4:
			displayGameRules();
			break;
		case 5:
			continueGame = false;
			break;
		default:
			printf("Not a valid menu option\n");
			break;
		}
	}

	return 0;
}
