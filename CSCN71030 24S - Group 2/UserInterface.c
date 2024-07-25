#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "UserInterface.h"


// Function definitions
void getUsername(char* username) {
    printf("Please enter your username: ");
    scanf("%s", username);
}

void startGame(int difficulty, char* username, int* initialGuess) {
    int guess[10];
    char input[10];
    int valid;

    if (initialGuess != NULL) {
        printf("\nResuming game at difficulty level %d with last guess: ", difficulty);
        for (int i = 0; i < difficulty + 3; i++) {
            printf("%d", initialGuess[i]);
        }
        printf("\n\n");
        memcpy(guess, initialGuess, 10 * sizeof(int));
    }
    else {
        printf("\nStarting game at difficulty level %d.\n\n", difficulty);
    }

    do {
        printf("Enter your guess (or type 'save' to pause and save the game): ");
        scanf("%s", input);

        if (strcmp(input, "save") == 0) {
            saveGame(difficulty, username, guess);
            printf("Game saved. You can resume later.\n");
            return;
        }

        for (int i = 0; i < difficulty + 3; i++) {
            guess[i] = input[i] - '0';
        }

        valid = isValidGuess(guess, difficulty);
        if (!valid) {
            printf("Invalid guess. Please try again.\n");
        }
    } while (!valid);

    printf("Your valid guess: %s\n", input);
}

void resumeGame(char* username) {
    int difficulty;
    int guess[10];

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
    printf("2. You need to guess the number. After each guess, you'll get feedback on how many\n");
    printf("   digits are correct and in the correct position (Bulls) and how many digits are correct but in the wrong position (Cows).\n");
    printf("3. The goal is to guess the number correctly in the fewest attempts.\n\n");
}

int isValidGuess(int* guess, int difficulty) {
    int expectedLength = difficulty + 3;

    for (int i = 0; i < expectedLength; i++) {
        if (!isdigit(guess[i] + '0')) {
            return 0;
        }
    }

    return 1;
}

void saveGame(int difficulty, char* username, int* guess) {
    // Implement game save logic here
}

int loadGame(int* difficulty, char* username, int* guess) {
    // Implement game load logic here
    return 0;
}

void gameMenu(int difficulty) {
    int choice;
    char username[50];

    printf("Welcome to the Rangers Arena\n");
    printf("Let's play BULLS and COWS\n\n");

    // Get username
    getUsername(username);

    // Main menu loop
    while (1) {
        printf("\n------ Menu -----\n");
        printf("1. Start Game\n");
        printf("2. Resume Last Game\n");
        printf("3. Game Rules\n");
        printf("4. Exit\n");
        printf("Please choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            startGame(difficulty, username, NULL);
            break;
        case 2:
            resumeGame(username);
            break;
        case 3:
            displayGameRules();
            break;
        case 4:
            printf("Exiting the game. Goodbye!\n");
            return;
        default:
            printf("Invalid option. Please try again.\n");
        }
    }
}
