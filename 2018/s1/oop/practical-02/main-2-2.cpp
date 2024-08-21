#include <iostream>


using namespace std;
extern int binary_to_number(int*, int);

int main() {
	int test[3] = {1,1,0};

	cout<<binary_to_number(test, 3)<<"\n";
}