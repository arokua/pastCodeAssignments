#include <iostream>
#include <stdlib.h>

extern int twofivenine(int*, int);
using namespace std;

int main(int argc,char **argv)
{
	int n;
	cout<< "Please enter the size of the array";
	cin >> n;
	while (n < 1){
		cout<< "Please enter the size of the array, exit the loop by enter an interger value larger than 0";
		cin >> n;
	}
	if (n >= 0){
		int testArray[n];

		if (n > 0){
			for (int i= 0; i < n; i++){
				cout<< "Please enter an interger";
				cin >> testArray[i];
			}
		}
		cout<< twofivenine(testArray, n);
	}

	
}

