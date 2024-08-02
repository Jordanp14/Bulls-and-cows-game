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

	int  value, bulls = 0, cows = 0, input;
	LEADERBOARD l = { 0 };
	char leaderboardDifficulty[7] = { 0 };
	bool continueGame = true;
	bool game_won = false;

	// seed the random
	srand((unsigned int)time(NULL));

	// read command line argument to get difficulty length
	l.guess_length = readDifficulty(argv[1]);

	//generate random int* for answer
	int* answer = (int*)malloc(l.guess_length * sizeof(int));
	if (answer == NULL)
	{
		printf("Could not allocate memory\t exiting...");
		exit(1);
	}
	answer = getRandomInt(l.guess_length);

	// temp for testing
	// print("%d", l.guess_length);
	printAnswer(answer, l.guess_length);

	int* guess = (int*)malloc(l.guess_length * sizeof(int));
	// check that memory was successfully allocated
	if (guess == NULL)
	{
		printf("Could not allocate memory\t exiting...");
		exit(1);
	}
	// add get username function 
	displayTitle();
	getUsername(l.username);


		// set command line argument to difficulty
		strncpy(l.difficulty, argv[1], strnlen(argv[1], 7));
	

	while (continueGame)
	{
		// game menu
		gameMenu();
		input = selectMenuOption();

		switch (input)
		{
		case 1:

			if (!Reload_Game_State(l.username, &l.score, guess, &l.guess_length, l.difficulty, answer, &game_won)) {
				printf("No previous game found.\n");
				break;
			}
			else if (game_won) {
				printf("You cannot reload your previous game as you already won it.\n");
				
				break;
			}
			else {
				printf("Game reloaded successfully.\n");
			}

		case 2:
			// Tell the user the difficulty
			printf("The game is set to %s\n", l.difficulty);

			// until the game has been won
			do
			{
				// get a guess from the user, if the first value is -1 then they typed "save" and the game should be paused
				getGuess(l.guess_length, guess);
				if (guess[0] == -1)
				{
					break;
				}

				//save game after each guess
				Save_Game_State(l, guess, answer, false);

				// add one to score
				l.score++;

				// validate guess
				bulls = validate_correct_position(guess, answer, l.guess_length);
				cows = validate_wrong_position(guess, answer, l.guess_length);
				//print results to user
				if (bulls == 1)
				{
					printf("There is 1 bull ");
				}
				else
				{
					printf("There are %d bulls ", bulls);
				}
				if (cows == 1)
				{
					printf("and 1 cow.\n");
				}
				else
				{
					printf("and %d cows.\n", cows);
				}

				if (bulls == l.guess_length)
				{
					printf("\nCongratulations! You won in %d turns!\n", l.score);
					Save_User_Score(l, guess);
					Save_Game_State(l, guess, answer, true);
					//continueGame = false;
				}

			} while (bulls != l.guess_length);
			break;

		case 3:
			displayGameRules();
			break;

		case 4:
		
			// ask for leaderboad display difficulty 
			do
			{
				printf("Which difficulty would you like to display?\n Easy\n Medium\n Hard\n");
				value = scanf("%s", leaderboardDifficulty);

			} while (value != 1 && readDifficulty(leaderboardDifficulty) != 4 &&
				readDifficulty(leaderboardDifficulty) != 5 && readDifficulty(leaderboardDifficulty) != 6);

			if (readDifficulty(leaderboardDifficulty) == 4)
			{
				strncpy(leaderboardDifficulty, "EASY", 7);
			}
			else if (readDifficulty(leaderboardDifficulty) == 5)
			{
				strncpy(leaderboardDifficulty, "MEDIUM", 7);
			}
			else if (readDifficulty(leaderboardDifficulty) == 6)
			{
				strncpy(leaderboardDifficulty, "HARD", 7);
			}
			// display leaderboard based on selected difficulty
			Display_Leaderboard(leaderboardDifficulty);
			break;
			
		case 5:
			continueGame = false;
			break;
		default:
			printf("Not a valid menu option\n");
			break;
		}
	}

	free(guess);
	free(answer);

	return 0;
}
