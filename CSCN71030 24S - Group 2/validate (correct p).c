#include <stdio.h>
#include <stdlib.h>
#include "validate (correct p).h"

//function to validate if the guessed numbers are in the correct position
bool* validate_correct_position(int* guess, int* target, int length) {

	//allocates memory for the resulting array
	bool* result = (bool*)malloc(sizeof(bool) * length);

	//checks if the allocation was successful
	if (result == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(1);
	}

	//loops through each element in the arrays
	for (int i = 0; i < length; i++) {
		//compares the corresponding elements of the guess and target arrays
		result[i] = (guess[i] == target[i]);
	}

	return result;

}