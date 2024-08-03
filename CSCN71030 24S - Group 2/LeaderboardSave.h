#pragma once
#include <stdbool.h>

//Leaderboard Save Module Interface

#define MAX_USERNAME_LENGTH 50
#define LEADERBOARD_FILE "leaderboard.txt"
#define GAMESTATE_FILE "gamestate.txt"
#define MAX_DIFFICULTY_LENGTH 10
#define MAX_DIFFICULTY 3
#define MAX_GUESS_LENGTH 100

// Structure to store leaderboard data
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    int score;
    char difficulty[MAX_DIFFICULTY_LENGTH];
    int guesses[MAX_DIFFICULTY][MAX_GUESS_LENGTH]; // 2D array to store guesses for different difficulty levels
    int guess_length[MAX_DIFFICULTY]; // Array to store the length of guesses for each difficulty level
} LEADERBOARD;

// Function Declarations
void Save_User_Score(LEADERBOARD l, int difficulty_index, int* guess);
void Save_Game_State(LEADERBOARD l, int* answer, bool game_won, int difficulty_index, int* guess);
bool Reload_Game_State(char* username, int* score, int* guess, int* guess_length, char* difficulty, int* answer, bool* game_won, int difficulty_index);
void Display_Leaderboard(char* difficulty);


