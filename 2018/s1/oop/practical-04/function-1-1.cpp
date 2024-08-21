#include <iostream>
#include <string>

using namespace std;

void copy_2d_strings(string first[][2], string second[][2], int n) {
	for (int r = 0; r < n; r++){
		for (int c = 0; c < 2; c++){
				second[r][c] = first[r][c];
		}
	}
	
}