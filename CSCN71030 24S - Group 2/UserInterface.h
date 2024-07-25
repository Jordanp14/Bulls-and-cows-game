#pragma once

// Function declarations
void getUsername(char* username);
void startGame(int difficulty, char* username, int* initialGuess);
void resumeGame(char* username);
void displayGameRules();
int isValidGuess(int* guess, int difficulty);
void saveGame(int difficulty, char* username, int* guess);
int loadGame(int* difficulty, char* username, int* guess);
void gameMenu(int difficulty);
