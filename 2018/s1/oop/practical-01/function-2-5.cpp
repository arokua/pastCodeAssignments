#include <iostream>

bool descending(int array[], int n){
	int first = array[0];
	if (n < 1){
		return false;
	}

	else {
		for(int i = 1; i < n; i ++){
			if (array[i] < first) {
				return true;
			}else{
				return false;
				break;
			}
		}
	}
}