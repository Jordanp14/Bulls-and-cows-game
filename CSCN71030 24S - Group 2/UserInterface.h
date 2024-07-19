#pragma once

// Function prototypes
void displayGameRules();
void startGame(int difficulty, char* username, char* initialGuess);
int isValidGuess(char* guess, int difficulty);
void saveGame(int difficulty, char* username, char* guess);
int loadGame(int* difficulty, char* username, char* guess);
void resumeGame(char* username);

