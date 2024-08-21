#include <iostream>

using namespace std;

void count_numbers(int array[4][4]){
	int n0 = 0;
	int n1 = 0;
	int n2 = 0;
	int n3 = 0;
	int n4 = 0;
	int n5 = 0;
	int n6 = 0;
	int n7 = 0;
	int n8 = 0;
	int n9 = 0;

	for (int r = 0; r < 4; r++){
		for (int c = 0; c < 4; c++){
			if (array[r][c] == 0)	 {
				n0 += 1;
			}else if (array[r][c] == 1)	 {
				n1 += 1;
			}else if (array[r][c] == 2)	 {
				n2 += 1;
			}else if (array[r][c] == 3)	 {
				n3 += 1;
			}else if (array[r][c] == 4)	 {
				n4 += 1;
			}else if (array[r][c] == 5)	 {
				n5 += 1;
			}else if (array[r][c] == 6)	 {
				n6 += 1;
			}else if (array[r][c] == 7)	 {
				n7 += 1;
			}else if (array[r][c] == 8)	 {
				n8 += 1;
			}else if (array[r][c] == 9)	 {
				n9 += 1;
			}
		}
	}

	cout << "0:" << n0 << ";1:" << n1 << ";2:" << n2 << ";3:" << n3 << ";4:" << n4 << ";5:" << n5 << ";6:" << n6 << ";7:" << n7 << ";8:" << n8 << ";9:" << n9 <<";\n";

}