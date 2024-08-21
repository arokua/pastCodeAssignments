#include <iostream>
#include <stdlib.h>

extern double sumeven(double*, int);
using namespace std;

int main(int argc,char **argv)
{
	double testArray[10] = { 1,2,3,4,5,6,7,8,9,10};
	
	cout<<"The sums of elements at even positions is: ";
	cout<< sumeven(testArray, 10);
}

