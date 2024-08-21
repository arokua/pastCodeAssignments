#include <iostream>
#include <string>

using namespace std;

extern void print_class(string*, string*, int[][4], int);

int main() {
	string cour[4] ={"A","B", "C", "D"};
	string stud[2] = {"Alah", "Jesus"};
	int n =2;

	int rc[2][4] = {{1,2,3,4}, {5,6,7,8}};
	

	print_class(cour, stud, rc, n);
}

