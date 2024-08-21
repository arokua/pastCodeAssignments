#include <iostream>

using namespace std;

int binary_to_number(int binary_digits[], int number_of_digits){
	int not0or1 = 0;
	int decimal = 0;
	int 2times2by;
	int atthatIndex = 2;
	if (number_of_digits > 0 or number_of_digits < 1){
		cout<< "Invalid array length.\n";
	}
	else {
		for (int i = 0; i< number_of_digits; i++ ){
			if (binary_digits[i] != 0){
					if (binary_digits[i] != 1){
						not0or1 += 1;
					}
				}
		}
		
		cout << not0or1<< "\n";

		if (not0or1 > 0) {
			cout << "This array contains at least 1 value that is not 0 or 1\n";

		}else {
			for (int n = 0; n < number_of_digits; n++){
				2times2by = length - i - 1;
				for ( int j = 1; j < 2times2by; j++ ) {
					atthatIndex *= j;


				}
			}
		} 
	}
}
