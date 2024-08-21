#include <iostream>
#include <string>
#include "musician.h"
#include "orchestra.h"

using namespace std;

int main(){
	orchestra Ope(20);
	musician llol("Guitar", 20);
	Ope.add_musician(llol);
	cout<< Ope.has_instrument("Pie")<<"\n";
}