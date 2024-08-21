#include <iostream>
#include <string>
using namespace std;


extern float arithmetic_ops(float , float,string);
int main(){
	float a =2.3;
	float b = 5.6;

	cout<< arithmetic_ops(a, b, "+")<< "\n";
	cout<< arithmetic_ops(a, b, "-")<< "\n";
}

