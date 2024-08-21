#include <iostream>
#include <math.h>
using namespace std;

int binary_to_number(int binary_digits[], int number_of_digits) {
	int finalnumber;

	int currentApow = 0;
	int just01 = 0;

	for (int e = 0; e < number_of_digits; e++){
		if (binary_digits[e] != 0 ){
			if (binary_digits[e] == 1) {
				just01 = just01;
			}else if(binary_digits[e] != 1){
				just01 += 1;
			}
			
		}
	}
	if (just01 > 0){
		cout<< "The array must only contains 0 and 1 as digits.";
		cout<<"\n";
	}else {
		for (int e = 0; e < number_of_digits; e++){
			currentApow = 1;
			for (int b = 0; b < e ; b++){
				if ( e!= 0){
					
					currentApow *= 2;
					
				}else {
					currentApow = 1;
				}

			}
			finalnumber += currentApow * binary_digits[number_of_digits - e - 1];
		}
		return finalnumber;
	}
	
}