#include <iostream>

using namespace std;

extern void count_numbers(int[][4]) ;

int main(int argc,char **argv){
	int mat1[4][4] = {{1,0,0,5}, {0,3,0,2}, {0,0,2,1},{0,0,2,1}};
	

	cout << "The following matrix" <<"\n";
	for (int r = 0; r < 3; r++){
		for (int c = 0; c < 3; c++){
			cout << mat1[r][c]<<"\t";
		}
		cout<< "\n";
		
	}
	cout<<"has";
	cout <<"\n";
	count_numbers(mat1);
	cout<<"\n";
	return 1;
}