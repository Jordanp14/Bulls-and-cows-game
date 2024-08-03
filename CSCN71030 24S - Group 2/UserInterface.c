//User Interface Module Implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "UserInterface.h"
#include "answer.h"


// Function definitions
void getUsername(char* username) {
    printf("Please enter your username: ");
    scanf("%s", username);
}

void getGuess(int difficulty, int* guess) {
    

    char input[10];
    int valid;

    do {
        printf("Enter your guess (or type 'save' to pause and save the game): ");
        scanf("%s", input);

        if (strcmp(input, "save") == 0) {
            guess[0] = -1;
            printf("Game saved. You can resume later.\n");
            return;
        }

        valid = isValidGuess(input, difficulty);
        if (!valid) {
            printf("Invalid guess. Please try again.\n");
        }
    } while (!valid);

    for (int i = 0; i < difficulty; i++) {
        guess[i] = input[i] - '0';
    }
   // printAnswer(guess, difficulty);

    //printf("Your valid guess: %s\n", input);
    
}

void displayTitle(void)
{
    printf("Welcome to the Rangers Arena\n");
    printf("Let's play BULLS and COWS\n\n");
}

void gameMenu(void) {

    // Main menu 
    printf("\n------ Menu -----\n");
    printf("1. Resume Last Game\n");
    printf("2. Start Game\n");
    printf("3. Game Rules\n");
    printf("4. Display Leaderboard\n");
    printf("5. Exit\n");
    printf("Please choose an option: ");
}


void displayGameRules() {
    printf("\nGame Rules:\n");
    printf("1. The game will generate a random number based on the selected difficulty.\n");
    printf("2. You need to guess the number. After each guess, you'll get feedback on how many digits are correct");
    printf("and in the correct position(Bulls) and how many digits are correct but in the wrong position(Cows).\n");
    printf("3. The goal is to guess the number correctly in the fewest attempts.\n\n");
}

// case switch was not needed because the expected length will already be known
int isValidGuess(char* guess, int expectedLength) {
    int length = (int)strlen(guess);

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