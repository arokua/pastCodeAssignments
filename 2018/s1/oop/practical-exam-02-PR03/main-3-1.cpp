#include <iostream>

using namespace std;

extern int welloff(int*, int ) ;

int main () {
	int testArray[6] ={1,2,3,4,5,20};

	cout<< welloff(testArray, 6) <<"\n";
}