#include <iostream>

using namespace std;

extern void print_summed_matrices(int[][3], int[][3]) ;

int main(int argc,char **argv){
	int mat1[3][3] = {{0,1,2},{3,4,5},{6,7,8}} ;
	int mat2[3][3] = {{0,1,2},{3,4,5},{6,7,8}} ;

	cout << "The following matrix" <<"\n";
	for (int r = 0; r < 3; r++){
		for (int c = 0; c < 3; c++){
			cout << mat1[r][c]<<"\t";
		}
		cout<< "\n";
		
	}
	cout <<"\n";


	for (int r = 0; r < 3; r++){
		for (int c = 0; c < 3; c++){
			cout << mat2[r][c]<<"\t";
		}
		cout<< "\n";
		
	}

	cout<< "added together is"<< "\n";
	print_summed_matrices(mat1, mat2);
	
}