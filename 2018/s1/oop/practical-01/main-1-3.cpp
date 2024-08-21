#include <iostream>
#include <stdlib.h>
using namespace std;
extern int count(int*,int,int);

int main(int argc,char **argv){
	int test1Array[6] = {1,2,3,4,4,6};
	int test2Array[0] = {};
	cout<< "The count is: ";
	cout<< count(test1Array, 6, 4);
	cout<<'\n';

	cout<< "The count is: ";
	cout<< count(test2Array, 0, 0);

}


