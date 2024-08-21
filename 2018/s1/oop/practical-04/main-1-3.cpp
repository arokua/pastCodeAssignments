#include <iostream>


using namespace std;

extern void cpyia(int*,int*,int);

int main() {
	int a1[4] = {1,2,3,4};
	int a2[4];

	cpyia(a1,a2,4);
}