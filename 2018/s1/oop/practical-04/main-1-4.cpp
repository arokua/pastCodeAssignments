#include <iostream>


using namespace std;

extern void cpyda(double *,double *,int);

int main() {
	double a1[2][2] = {{1,2},{3,4}};
	double a2[2][2];

	double *p1 = &a1[0][0];
    double *p2= &a2[0][0];

	cpyda(p1,p2,2);
}