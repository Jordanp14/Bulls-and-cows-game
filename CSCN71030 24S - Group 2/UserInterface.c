#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "UserInterface.h"

void startGame(int difficulty, char* username, char* initialGuess) {
    char guess[10];
    int valid;

    if (initialGuess != NULL) {
        printf("\nResuming game at difficulty level %d with last guess %s.\n\n", difficulty, initialGuess);
        strcpy(guess, initialGuess);
    }
    else {
        printf("\nStarting game at difficulty level %d.\n\n", difficulty);
    }

    do {
        printf("Enter your guess (or type 'save' to pause and save the game): ");
        scanf("%s", guess);

        if (strcmp(guess, "save") == 0) {
            saveGame(difficulty, username, guess);
            printf("Game saved. You can resume later.\n");
            return;
        }

        valid = isValidGuess(guess, difficulty);
        if (!valid) {
            printf("Invalid guess. Please try again.\n");
        }
    } while (!valid);

    // Implement the rest of the game logic here
    printf("Your valid guess: %s\n", guess);
}

void resumeGame(char* username) {
    int difficulty;
    char guess[10];

    if (loadGame(&difficulty, username, guess)) {
        startGame(difficulty, username, guess);
    }
    else {
        printf("No saved game found or error loading the game.\n");
    }
}

void displayGameRules() {
    printf("\nGame Rules:\n");
    printf("1. The game will generate a random number based on the selected difficulty.\n");
    printf("2. You need to guess the number. After each guess, you'll get feedback on how many digits are correct");
    printf("and in the correct position(Bulls) and how many digits are correct but in the wrong position(Cows).\n");
    printf("3. The goal is to guess the number correctly in the fewest attempts.\n\n");
}

int isValidGuess(char* guess, int difficulty) {
    int length = strlen(guess);
    int expectedLength;

    switch (difficulty) {
    case 1:
        expectedLength = 4;
        break;
    case 2:
        expectedLength = 5;
        break;
    case 3:
        expectedLength = 6;
        break;
    default:
        return 0;
    }

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

void saveGame(int difficulty, char* username, char* guess) {
    // Implement game save logic here
}

int loadGame(int* difficulty, char* username, char* guess) {
    // Implement game load logic here
    return 0; // Return 1 if loading is successful, otherwise 0
}
