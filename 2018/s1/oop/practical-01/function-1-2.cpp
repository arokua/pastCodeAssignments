#include <iostream>
double average(int array[], int n) {
	int theSum = 0.0;
	
	if (n < 1) {
		return 0;
	}else {
		for (int i = 0; i < n; i++) {
			theSum += array[i];
		}
	
		average = theSum / n;
		return average;
    }
}
