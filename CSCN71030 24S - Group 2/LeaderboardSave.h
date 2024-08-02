#pragma once
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 50
#define LEADERBOARD_FILE "leaderboard.txt"
#define GAMESTATE_FILE "gamestate.txt"
#define MAX_DIFFICULTY_LENGTH 10

typedef struct Leaderboard
{
	char username[MAX_USERNAME_LENGTH];
	int score;
	int guess_length;
	char difficulty[MAX_DIFFICULTY_LENGTH];
}LEADERBOARD, * PLEADERBOARD;

// Function Declarations
void Save_User_Score(LEADERBOARD l, int* guess);
void Save_Game_State(LEADERBOARD l, int* guess, int* answer, bool game_won);
bool Reload_Game_State(char* username, int* score, int* guess, int* guess_length, char* difficulty, int* answer, bool* game_won);
void Display_Leaderboard(char* difficulty);


