#include <iostream>

using namespace std;

void print_summed_matrices(int array1[3][3],int array2[3][3]){
	int finalarray[3][3] ={{0,0,0}, {0,0,0}, {0,0,0}} ;
	for (int r = 0; r < 3; r++){
		for (int c = 0; c < 3; c++){
			finalarray[r][c] += array1[r][c] + array2[r][c];; 
		}
	}

	for (int r = 0; r < 3; r++){
		for (int c = 0; c < 3; c++){
			cout << finalarray[r][c] <<" ";
		}
		cout<< "\n";
		
	}
}