// Guess Validation (wrong position) Module Implementation

#include "validateWrongPosition.h"

// Function is not finished, still has errors that need to be fixed (repeating numbers)

int validate_wrong_position(int* guess, int* target, int length) {

	int count = 0;
	for (int i = 0; i < length; i++) {
		int match_count = 0;
		for (int j = 0; j < length; j++) {
			if ((i != j) && (guess[i] == target[j]) && (match_count == 0)) {
				count++;
				match_count++;
			}
		}
	}
	return count;
}