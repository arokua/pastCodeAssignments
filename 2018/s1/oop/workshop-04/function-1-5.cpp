#include <iostream>

using namespace std;

int size_of_array_arr() {
	int mooo[3] = {1,2,3};
	int *arr = new int[3];
	arr = &mooo[0];
	return sizeof(mooo);

}