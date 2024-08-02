#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LeaderboardSave.h"

// Save User Score Function
void Save_User_Score(LEADERBOARD l, int* guess) {
    FILE* file = fopen(LEADERBOARD_FILE, "a");
    if (!file) {
        perror("Failed to open leaderboard file for writing");
        return;
    }

    //writing user information to the file
    fprintf(file, "%s %d %s Guess: ", l.username, l.score, l.difficulty);

    // writing the guesses to the file
    for (int i = 0; i < l.guess_length; ++i) {
        fprintf(file, "%d ", guess[i]);
    }

    //ending line after guesses
    fprintf(file, "\n");
    fclose(file);
}

// Save Game State Function
void Save_Game_State(LEADERBOARD l, int* guess, int* answer, bool game_won) {
    FILE* file = fopen(GAMESTATE_FILE, "w");
    if (!file) {
        perror("Failed to open game state file for writing");
        return;
    }

    //writing the game state information to the file
    fprintf(file, "%s %d %d %s %d\n", l.username, l.score, l.guess_length, l.difficulty, game_won);

    //writing the guesses to the file
    for (int i = 0; i < l.guess_length; ++i) {
        fprintf(file, "%d ", guess[i]);
    }
    fprintf(file, "\n");

    //writing the answers to the file
    for (int i = 0; i < l.guess_length; ++i) {
        fprintf(file, "%d ", answer[i]);
    }
    fprintf(file, "\n");

    fclose(file);
}


// Reload Game State Function
bool Reload_Game_State(char* username, int* score, int* guess, int* guess_length, char* difficulty, int* answer, bool* game_won) {
    FILE* file = fopen(GAMESTATE_FILE, "r");
    if (!file) {
        perror("Failed to open game state file for reading");
        return false;
    }

    // variables to hold the read data
    char saved_username[MAX_USERNAME_LENGTH];
    int saved_score;
    int saved_guess_length; //specifies the count of guesses.
    char saved_difficulty[MAX_DIFFICULTY_LENGTH];
    int saved_game_won;

    // reading the data from the file
    while (fscanf_s(file, "%49s %d %d %9s %d", saved_username, (unsigned)sizeof(saved_username), &saved_score, &saved_guess_length, saved_difficulty, (unsigned)sizeof(saved_difficulty), &saved_game_won) != EOF) {
        if (strcmp(saved_username, username) == 0) {
            *score = saved_score;
            *guess_length = saved_guess_length;
            strcpy_s(difficulty, MAX_DIFFICULTY_LENGTH, saved_difficulty);
            *game_won = saved_game_won;
            for (int i = 0; i < saved_guess_length; ++i) {
                fscanf_s(file, "%d", &guess[i]);
            }

            for (int i = 0; i < saved_guess_length; ++i) {
                fscanf_s(file, "%d", &answer[i]);
            }

            fclose(file);
            return true;
        }
        // Skip reading the guess values if the username doesn't match
        for (int i = 0; i < saved_guess_length; ++i) {
            fscanf_s(file, "%d", &saved_guess_length);
        }
        for (int i = 0; i < saved_guess_length; ++i) {
            fscanf_s(file, "%d", &saved_guess_length);
        }


    }

    fclose(file);
    return false;
}

// Display Leaderboard Function
void Display_Leaderboard(char* difficulty) {
    FILE* file = fopen(LEADERBOARD_FILE, "r");
    if (!file) {
        perror("Failed to open leaderboard file for reading");
        return;
    }

    printf("Leaderboard (%s):\n", difficulty);

    // Print headers
    printf("%-15s %-6s %-15s %-15s\n", "Username", "Score", "Difficulty", "Guessed Number");

    LEADERBOARD l = { 0 };
    char line[256]; //buffer to read lines from the file LEADERBOARD_FILE into memory
    while (fgets(line, sizeof(line), file)) {
        char* guess_part = strstr(line, "Guess:");
        if (guess_part != NULL) {
            // Scan the user data
            sscanf(line, "%49s %d %9s", l.username, &l.score, l.difficulty);

            if (strcmp(l.difficulty, difficulty) == 0) {
                // Extract the guessed numbers
                char guessed_numbers[100];
                strcpy(guessed_numbers, guess_part + strlen("Guess:"));

                // Remove the newline character from guessed_numbers
                guessed_numbers[strcspn(guessed_numbers, "\n")] = 0;
                
                // Print each entry
                printf("%-15s %-6d %-15s %-30s\n", l.username, l.score, l.difficulty, guessed_numbers);
            }
        }
    }

    fclose(file);
}
