#include <iostream>

using namespace std;

int* allocate(int n) {
	// Create a new array
	int * arra = new int[n];

	// Add the required elements to said array
	for (int i = 0; i < n; i++) {
		*(arra + i) = i + 1;
	}

	// return that array
	return arra;
}