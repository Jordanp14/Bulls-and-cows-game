// Guess Validation (wrong position) Module Implementation

#include "validateWrongPosition.h"

// Function is not finished, still has errors that need to be fixed (repeating numbers)

int validate_wrong_position(int* guess, int* target, int length) {

	int count = 0;
	for (int i = 0; i < length; i++) { // i iterates through guess array
		int prev_occurances = 0;
		for (int j = 0; j < i; j++) { // j iterates through guess array before index i
			if (guess[j] == guess[i]) { // check for previous occcurances of same element
				prev_occurances++;
			}
		}
		int match_count = 0;
		for (int k = 0; k < length; k++) { // k iterates through target array
			if ((guess[i] == target[k]) && (i != k) && (guess[k] != target[k])) { // check: values are equal, not at same index
				match_count++;
			}
			if (match_count > prev_occurances) { // check match hasn't been counted for previous occurance of value
				count++;
				break;
			}
		}
	}
	return count;
}