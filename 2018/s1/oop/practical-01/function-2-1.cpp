#include <iostream>
int minimum(int array[], int n) {
	
	if (n < 1){
		return 0;
	}
	else {
		int min = array[0];
		for (int i = 1; i < n; i++) {
			if (array[i] < min){
				min = array[i];
			}
		}
		return min;
	}
	
}
