#include <iostream>
#include <string>

using namespace std;

extern void copy_2d_strings(string [][2], string[][2], int);

int main() {
	string no1[3][2] = {{"ER","OP"},{"ER","OP"},{"ER","OP"}};
	string no2[3][2];

	copy_2d_strings(no1, no2, 3);

	

}