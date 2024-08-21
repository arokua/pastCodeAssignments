#include <iostream>

using namespace std;

extern int* readNumbers();
extern int  secondSmallestSum(int *, int );

int main() {
	int *eeray =readNumbers();
	cout << secondSmallestSum(eeray, 10) << "\n";
}