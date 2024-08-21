#include <iostream>
#include <stdlib.h>

extern int sumtwo(int*, int*, int);
using namespace std;

int main(int argc,char **argv)
{
	int test1Array[7] = { 1,2,3,4,5,6,7};
	int test2Array[7] = { 78,789,8979,7979,7978,97897};
	
	cout<<"The sum of the two arrays is: ";
	cout<< sumtwo(test1Array, test2Array, 7);

}

