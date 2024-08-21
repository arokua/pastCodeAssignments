#include <iostream>
#include <stdlib.h>

extern int maximum(int*, int);
using namespace std;

int main(int argc,char **argv)
{
	int testArray[10] = { 100,2,-3,4,554164,6,7,518,-958888888,10};
	
	
	cout<<" '\n' The max value of the given array is: ";

	cout<< maximum(testArray, 10);
}

