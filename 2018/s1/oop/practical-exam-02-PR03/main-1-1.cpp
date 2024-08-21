#include <iostream>

using namespace std;

extern int* allocate(int );

int main() {
	// Create the number of elements for the allocate function.
	int num ;
	cin >> num;
	allocate(num);
}