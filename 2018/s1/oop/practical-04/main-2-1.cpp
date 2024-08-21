#include <iostream>


using namespace std;

extern  void print_sevens(int *nums,int );

int main() {
	int a1[4] = {1,2,3,14};
	int *p = &a1[0];

	print_sevens(p, 4);
}