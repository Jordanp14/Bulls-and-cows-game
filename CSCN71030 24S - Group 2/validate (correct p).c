#include <stdio.h>
#include <stdlib.h>
#include "validate (correct p).h"

#define SIZE_MESSAGE 100
//function to validate if the guessed numbers are in the correct position
int validate_correct_position(int* guess, int* target, int length) {
	int correct_position = 0;

	//counts the number of correct positions
	for (int i = 0; i < length; i++) {
		if (guess[i] == target[i]) {
			correct_position++;
		}
	}
	
	//prints the number of correct positions
	//printf("There are %d number%s in the correct position.\n", correct_position, correct_position == 1 ? "" : "s");

	return correct_position;

}