#pragma once

//User Interface Module Interface

void displayGameRules();
int isValidGuess(char* guess, int difficulty);
void getGuess(int difficulty, int* guess);
void displayTitle(void);
void gameMenu(void);
void getUsername(char* username);
int selectMenuOption(void);