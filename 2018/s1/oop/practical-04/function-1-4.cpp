#include <iostream>

using namespace std;

void cpyda(double *old_array,double *new_array,int length) {
	for (int i = 0; i <length; i++){
		for (int j = 0; j< length ;j++){
			*(new_array + i) = *(old_array + i);
		}
	}
}