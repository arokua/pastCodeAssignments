#include <iostream>
#include <stdlib.h>

extern int ascending(int*, int);
using namespace std;

int main(int argc,char **argv)
{
	int testArray[5] = {1,2,3,4,5};
	cout<< ascending(testArray, 5);	
}

