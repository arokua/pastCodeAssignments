#include <iostream>
int count(int array[], int n, int number){
	int theCount1 = 0;
	
	if (n < 1) {
		return 0;
	}
	else {
		for (int i = 0; i < n; i++) {
			if ( array[i] == number) {
				theCount1 += 1;
			}
		}
	
	return theCount1;
    }
}
