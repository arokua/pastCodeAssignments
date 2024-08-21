#include <iostream>
#include <stdlib.h>

extern int minimum(int*, int);
using namespace std;

int main(int argc,char **argv)
{
	int testArray[10] = { 100,2,-3,4,5,6,7,8,-9,0};
	
	cout<<"The min of the given array is: ";
	cout<< minimum(testArray, 10);
}

