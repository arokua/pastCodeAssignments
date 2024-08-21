#include <iostream>
using namespace std;
//The task requires to print out the result so no return value
void twofivenine(int array[], int n) {
	if (n < 1){
		cout<< "The array is empty!";
	}
	else {

		int twoAmount = 0;
		int fiveAmount = 0;
		int nineAmount = 0;
		for (int i = 0; i < n; i++) {
			if (array[i] == 2){
				twoAmount += 1;
			}

			else if (array[i] == 5){
				fiveAmount += 1;
			}

			else if (array[i] == 9){
				nineAmount += 1;
			}
		}

		cout<< "2:"; cout<< twoAmount; cout<< ";5:"; cout<< fiveAmount; cout<< ",9:"; cout<< nineAmount;
		cout<< endl;
		
	}
}
