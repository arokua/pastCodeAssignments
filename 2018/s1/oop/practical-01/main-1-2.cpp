#include <iostream>
#include <stdlib.h>

extern double average(int*, int);
using namespace std;

int main(int argc,char **argv)
{
	int testArray[10] = { 1,2,3,4,5,6,7,8,9,10};
	
	cout<<"The average is: ";
	cout<< average(testArray, 10);
}

