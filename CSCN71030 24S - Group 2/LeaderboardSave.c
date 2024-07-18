#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LeaderboardSave.h"

// Save User Score Function
void Save_User_Score(char* username, int score, int* guess, int guess_length, char* difficulty) {
    FILE* file = fopen(LEADERBOARD_FILE, "a");
    if (!file) {
        perror("Failed to open leaderboard file for writing");
        return;
    }

    fprintf(file, "%s %d %s Guess: ", username, score, difficulty);
    for (int i = 0; i < guess_length; ++i) {
        fprintf(file, "%d ", guess[i]);
    }
    fprintf(file, "\n");
    fclose(file);
}

// Save Game State Function
void Save_Game_State(char* username, int score, int* guess, int guess_length, char* difficulty) {
    FILE* file = fopen(GAMESTATE_FILE, "w");
    if (!file) {
        perror("Failed to open game state file for writing");
        return;
    }

    fprintf(file, "%s %d %d %s\n", username, score, guess_length, difficulty);
    for (int i = 0; i < guess_length; ++i) {
        fprintf(file, "%d ", guess[i]);
    }
    fprintf(file, "\n");

    fclose(file);
}

bool Reload_Game_State(char* username, int* score, int* guess, int* guess_length, char* difficulty) {
    FILE* file = fopen(GAMESTATE_FILE, "r");
    if (!file) {
        perror("Failed to open game state file for reading");
        return false;
    }

    char saved_username[MAX_USERNAME_LENGTH];
    int saved_score;
    int saved_guess_length; //specifies the count of guesses.
    char saved_difficulty[MAX_DIFFICULTY_LENGTH];
    while (fscanf_s(file, "%49s %d %d %9s", saved_username, (unsigned)sizeof(saved_username), &saved_score, &saved_guess_length, saved_difficulty, (unsigned)sizeof(saved_difficulty)) != EOF) {
        if (strcmp(saved_username, username) == 0) {
            *score = saved_score;
            *guess_length = saved_guess_length;
            strcpy_s(difficulty, MAX_DIFFICULTY_LENGTH, saved_difficulty);
            for (int i = 0; i < saved_guess_length; ++i) {
                fscanf_s(file, "%d", &guess[i]);
            }
            fclose(file);
            return true;
        }
        // Skip reading the guess values if the username doesn't match
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
    printf("%-15s %-6s %-15s %-15s\n", "Username", "Score", "Difficulty", "Number of guesses");

    char username[MAX_USERNAME_LENGTH];
    int score;
    char saved_difficulty[MAX_DIFFICULTY_LENGTH];
    int guess_count;
    char line[256]; //buffer to read lines from the file LEADERBOARD_FILE into memory
    while (fgets(line, sizeof(line), file)) {
        sscanf_s(line, "%49s %d %9s Guess: %n", username, (unsigned)sizeof(username), &score, saved_difficulty, (unsigned)sizeof(saved_difficulty), &guess_count);

        if (strcmp(saved_difficulty, difficulty) == 0) {
            // Print each entry
            printf("%-15s %-6d %-15s %-15d\n", username, score, saved_difficulty, guess_count / 2); // Divide by 2 to get the number of guesses
        }
    }

    fclose(file);
}