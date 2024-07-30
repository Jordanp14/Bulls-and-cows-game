#pragma once

// Function prototypes
void displayGameRules();
//void startGame(int difficulty, char* username, char* initialGuess);
int isValidGuess(char* guess, int difficulty);
//void resumeGame(char* username);
void getGuess(int difficulty, int* guess);
void displayTitle(void);
void gameMenu(void);
void getUsername(char* username);
int selectMenuOption(void);