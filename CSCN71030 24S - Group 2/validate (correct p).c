//Guess Validation (correct position) Module Implementation

#include <stdio.h>
#include <stdlib.h>
#include "validate (correct p).h"


//function to validate if the guessed numbers are in the correct position
int validate_correct_position(int* guess, int* target, int length) {
	int correct_position = 0;

	//counts the number of correct positions
	for (int i = 0; i < length; i++) {
		if (guess[i] == target[i]) {
			correct_position++;
		}
	}

	return correct_position;

}