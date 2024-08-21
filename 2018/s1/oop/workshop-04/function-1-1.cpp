#include <iostream>

using namespace std;

int size_of_variable_star_t(){
	int a, *p;
	int *t = new int;
	p = &a;

	return sizeof(t);

}