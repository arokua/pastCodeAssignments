#include <iostream>


using namespace std;
extern void printer(int[][10]);

int main() {
	int testza[10][10] = {{1,2,3,4,5,6,7,8,9,0},{0,1,2,3,4,5,6,7,8,9},{9,0,1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8,9},{1,2,3,4,5,6,7,8,9,0},{1,2,3,4,5,6,7,8,9,0},{1,2,3,4,5,6,7,8,9,0},{1,2,3,4,5,6,7,8,9,0},{1,2,3,4,5,6,7,8,9,0},{1,2,3,4,5,6,7,8,9,0}};

	printer(testza);
}