#include <iostream>
#include <string>
using namespace std;

extern float add_op(float, float );
extern float subtrac_op(float, float );
extern float multiply_op(float, float );

extern float arithmetic_ops(float , float,float (*op)(float,float) );
int main(){
	float a =2.3;
	float b = 5.6;

	cout<< arithmetic_ops(a, b, &add_op)<< "\n";

}

