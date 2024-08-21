#include <iostream>

using namespace std;

int welloff(int vals[], int length) {
	int sum1 = 0; /* this variable would be the sum of all the variable up to the variable 
					that is being checked whether it is welloff */
	
	int noOfWellOff = 0; /* this variable counts how many well off
	 						element are there in the given array.
	 						The function would return this variable.*/

	

	for (int i = 0; i < length; i++) {
		// i is The index of element x, where x is the one stated in the question
		for (int j = 0; j < i; j++ ) {
			sum1 += vals[j];
		}

		if (sum1 <= vals[i]) {
			noOfWellOff += 1;
		}
		sum1 = 0;
	}

	return noOfWellOff;

}