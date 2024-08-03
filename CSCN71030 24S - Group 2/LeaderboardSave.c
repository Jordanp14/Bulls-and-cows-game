//Leaderboard Save Module Implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LeaderboardSave.h"

// Save User Score Function
void Save_User_Score(LEADERBOARD l, int difficulty_index, int* guess) {
    FILE* file = fopen(LEADERBOARD_FILE, "a");
    if (!file) {
        perror("Failed to open leaderboard file for writing");
        return;
    }

    // Write the username, score, and difficulty to the file
    fprintf(file, "%s %d %s Guess: ", l.username, l.score, l.difficulty);
    // Save the guesses to the 2D array
    for (int i = 0; i < l.guess_length[difficulty_index]; ++i) {
        l.guesses[difficulty_index][i] = guess[i];
        fprintf(file, "%d ", l.guesses[difficulty_index][i]);
    }

    fprintf(file, "\n");
    fclose(file);
}

// Save Game State Function
void Save_Game_State(LEADERBOARD l, int* answer, bool game_won, int difficulty_index, int* guess ) {
    FILE* file = fopen(GAMESTATE_FILE, "w");
    if (!file) {
        perror("Failed to open game state file for writing");
        return;
    }

    // Write the game state details to the file
    fprintf(file, "%s %d %d %s %d\n", l.username, l.score, l.guess_length[difficulty_index], l.difficulty, game_won);

    // Save the guesses to the file
    for (int i = 0; i < l.guess_length[difficulty_index]; ++i) {
        l.guesses[difficulty_index][i] = guess[i];
        fprintf(file, "%d ", l.guesses[difficulty_index][i]);
    }

    fprintf(file, "\n");

    // Save the answer to the file
    for (int i = 0; i < l.guess_length[difficulty_index]; ++i) {
        fprintf(file, "%d ", answer[i]);
    }
    fprintf(file, "\n");

    fclose(file);
}

// Reload Game State Function
bool Reload_Game_State(char* username, int* score, int* guess, int* guess_length, char* difficulty, int* answer, bool* game_won, int difficulty_index) {
    FILE* file = fopen(GAMESTATE_FILE, "r");
    if (!file) {
        perror("Failed to open game state file for reading");
        return false;
    }

    LEADERBOARD l = { 0 }; // Initialize a LEADERBOARD structure for reading data
    char saved_username[MAX_USERNAME_LENGTH];
    int saved_score;
    int saved_guess_length;
    char saved_difficulty[MAX_DIFFICULTY_LENGTH];
    int saved_game_won;

    // Read each line from the file
    while (fscanf(file, "%49s %d %d %9s %d", saved_username, &saved_score, &saved_guess_length, saved_difficulty, &saved_game_won) != EOF) {
        // Check if the saved data matches the current username and difficulty
        if (strcmp(saved_username, username) == 0 && strcmp(saved_difficulty, difficulty) == 0) {
            *score = saved_score;
            *guess_length = saved_guess_length;
            strcpy(difficulty, saved_difficulty);
            *game_won = saved_game_won;

            // Read guesses into the 2D array
            for (int i = 0; i < saved_guess_length; ++i) {
                fscanf(file, "%d", &l.guesses[difficulty_index][i]);
                guess[i] = l.guesses[difficulty_index][i];
            }

            // Read the answer from the file
            for (int i = 0; i < saved_guess_length; ++i) {
                fscanf(file, "%d", &answer[i]);
            }

            fclose(file);
            return true;
        }


        // Skip the guesses and answers if they don't match
        for (int i = 0; i < saved_guess_length; ++i) {
            fscanf(file, "%d", &saved_guess_length);
        }
        for (int i = 0; i < saved_guess_length; ++i) {
            fscanf(file, "%d", &saved_guess_length);
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

    printf("%-15s %-6s %-15s %-15s\n", "Username", "Score", "Difficulty", "Guessed Number");

    LEADERBOARD l = { 0 };
    char line[256];
    // Read each line from the leaderboard file
    while (fgets(line, sizeof(line), file)) {
        char* guess_part = strstr(line, "Guess:");
        if (guess_part != NULL) {
            // Extract the user data from the line
            sscanf(line, "%49s %d %9s", l.username, &l.score, l.difficulty);

            // Check if the difficulty matches
            if (strcmp(l.difficulty, difficulty) == 0) {
                char guessed_numbers[100];
                strcpy(guessed_numbers, guess_part + strlen("Guess:"));
                guessed_numbers[strcspn(guessed_numbers, "\n")] = 0;

                // Print the leaderboard entry
                printf("%-15s %-6d %-15s %-30s\n", l.username, l.score, l.difficulty, guessed_numbers);
            }
        }
    }

    fclose(file);
}
