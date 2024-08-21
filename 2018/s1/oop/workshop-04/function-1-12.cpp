#include <iostream>

using namespace std;

int size_of_variable_star_arr() {
	int *arr = new int[3];
	delete[] arr;
	return sizeof(arr);

}