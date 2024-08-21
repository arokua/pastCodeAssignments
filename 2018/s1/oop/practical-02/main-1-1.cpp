#include <iostream>

using namespace std;

extern int diagonal(int[][4]) ;

int main(int argc,char **argv){
	int mat1[4][4] = {{1,2,3,4},{1,2,3,4}, {1,2,3,4} ,{5,6,89,4}};
	cout << "The diagonal sum of the following matrix" <<"\n";
	for (int r = 0; r < 4; r++){
		for (int c = 0; c < 4; c++){
			cout << mat1[r][c]<<"\t";
		}
		cout<< "\n";
	}
	cout << "is: " << diagonal(mat1) << "\n" ;
	return 1;
}