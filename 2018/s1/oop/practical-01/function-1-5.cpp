#include <iostream>
int counteven(int number) {
	int theSum = 0;
	for (int i = 0; i < number; i++) {
		if ( i % 2 == 0){
			theSum += i;
		}
	}
	return theSum;
}
