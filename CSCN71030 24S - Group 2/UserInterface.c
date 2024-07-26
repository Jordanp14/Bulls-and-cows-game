#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "UserInterface.h"
#include "LeaderboardSave.h"

//redundant

//void startGame(char* difficulty, char* username, char* initialGuess) {
//    int guess[10];
//    int valid;
//
//    if (initialGuess != NULL) {
//        printf("\nResuming game at difficulty level %s with last guess %s.\n\n", difficulty, initialGuess);
//        strcpy(guess, initialGuess);
//    }
//    else {
//        printf("\nStarting game at difficulty level %s.\n\n", difficulty);
//    }
//
//}

int* getGuess(int difficulty, char* username)
{
    int valid;

    char* guess = (char*)malloc(difficulty * sizeof(char));
    // check that memory was successfully allocated
    if (guess == NULL)
    {
        printf("Could not allocate memory\t exiting...");
        exit(1);
    }

    int* intGuess = (int*)malloc(difficulty * sizeof(int));
    // check that memory was successfully allocated
    if (intGuess == NULL)
    {
        printf("Could not allocate memory\t exiting...");
        exit(1);
    }

    do {
        printf("Enter your guess (or type 'save' to pause and save the game): ");
        scanf("%s", guess);

        if (strcmp(guess, "save") == 0) {
            intGuess[0] = -1;
            return intGuess;
        }

        valid = isValidGuess(guess, difficulty);
        if (!valid) {
            printf("Invalid guess. Please try again.\n");
        }
    } while (!valid);


    // convert guess from char* to int*
    for (int i = 0; i < difficulty; i++)
    {
        intGuess[i] = (int)guess[i];
    }

    // Implement the rest of the game logic here
    printf("Your valid guess: %s\n", guess);
    //free(guess);

    return intGuess;
}

//redundant

//void resumeGame(char* username) {
//    char difficulty[10];
//    int* score = 4;
//    char guess[10];
//    int guess_length = 4;
//
//    if (Reload_Game_State(username, score, guess, guess_length, difficulty)) {
//        startGame(difficulty, username, guess);
//    }
//    else {
//        printf("No saved game found or error loading the game.\n");
//    }
//}

void displayGameRules() {
    printf("\nGame Rules:\n");
    printf("1. The game will generate a random number based on the selected difficulty.\n");
    printf("2. You need to guess the number. After each guess, you'll get feedback on how many digits are correct");
    printf("and in the correct position(Bulls) and how many digits are correct but in the wrong position(Cows).\n");
    printf("3. The goal is to guess the number correctly in the fewest attempts.\n\n");
}

// case switch was not needed because the expected length will already be known
int isValidGuess(char* guess, int expectedLength) {
    int length = strlen(guess);

    if (length != expectedLength) {
        return 0;
    }

    for (int i = 0; i < length; i++) {
        if (!isdigit(guess[i])) {
            return 0;
        }
    }

    return 1;
}

int selectMenuOption(void)
{
    int value, input;

    // keep asking for input until valid input is accepted
    do
    {
        value = scanf("%d", &input);
        int c;
        if (value != 1)
        {
        
        //check for unrecoverable error
        if (value == EOF)
        {
            fprintf(stderr, "Unrecoverable input error!\n");
            exit(EXIT_FAILURE);
        }

        //print error message
        printf("Input not accepted\n");

        do
        {
            c = getchar();

        } while (c != EOF && c != '\n');
    }
    } while (value != 1);

    return input;
}