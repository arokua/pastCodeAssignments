#include <iostream>

using namespace std;

void print_scaled_matrix(int array[3][3],int scale){

	for (int r = 0; r < 3; r++){
		for (int c = 0; c < 3; c++){
			array[r][c] *= scale;
		}
	}

	for (int r = 0; r < 3; r++){
		for (int c = 0; c < 3; c++){
			cout << array[r][c] <<" ";
		}
		cout<< "\n";
		
	}
}