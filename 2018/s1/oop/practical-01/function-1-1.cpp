#include <iostream>
int sum_array(int array[], int n) {
	int theSum = 0;
	for (int i = 0; i < n; i++) {
		theSum += array[i];
	}
	return theSum;
}
