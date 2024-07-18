#pragma once
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 50
#define LEADERBOARD_FILE "leaderboard.txt"
#define GAMESTATE_FILE "gamestate.txt"
#define MAX_DIFFICULTY_LENGTH 10

// Function Declarations
void Save_User_Score(char* username, int score, int* guess, int guess_length, char* difficulty);
void Save_Game_State(char* username, int score, int* guess, int guess_length, char* difficulty);
bool Reload_Game_State(char* username, int* score, int* guess, int* guess_length, char* difficulty);
void Display_Leaderboard(char* difficulty);
