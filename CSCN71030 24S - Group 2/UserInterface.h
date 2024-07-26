#pragma once

// Function prototypes
void displayGameRules();
//void startGame(int difficulty, char* username, char* initialGuess);
int isValidGuess(char* guess, int difficulty);
//void resumeGame(char* username);
int* getGuess(int difficulty);
void displayTitle(void);
void gameMenu(void);
void getUsername(char* username);
int selectMenuOption(void);