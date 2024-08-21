#include <iostream>

using namespace std;

void cpyia(int old_array[],int new_array[],int length) {
	/*int * aptr;
	int * p =new int[length];
	int * np = new int[length];
	np = &new_array[0];

	aptr = &old_array[0];
	p = aptr;
	for (int i =0; i < length; i ++){
		*(np + i) = *(p + i);

	}
		cout<< "\n";
	*/

	for (int i =0; i < length; i ++){
		*(new_array+i)=*(old_array+i);

	}



}