#include <iostream>

using namespace std;

extern void print_scaled_matrix(int[][3], int) ;

int main(int argc,char **argv){
	int mat1[3][3] = {{0,1,2},{3,4,5},{6,7,8}} ;
	int n =5;

	cout << "The following matrix" <<"\n";
	for (int r = 0; r < 3; r++){
		for (int c = 0; c < 3; c++){
			cout << mat1[r][c]<<"\t";
		}
		cout<< "\n";
		
	}
	cout<< "when scaled up"<< n <<"times, becomes: "<< "\n";
	print_scaled_matrix(mat1, n);
	
}