#include <iostream>
#include <stdlib.h>

extern int ascending(int*, int);
using namespace std;

int main(int argc,char **argv)
{
	int testArray[5] = {5,4,3,2,1};
	cout<< ascending(testArray, 5);	
}

