#include <iostream>
#include "person.h"
#include "aircraft.h"

#include <string>

using namespace std;

aircraft::aircraft(string cS, person Pi, person coPi){
	callsign = cS;
	A =Pi;
	B = coPi;
}

void aircraft::setPilot(person mP){
	A = mP;
}
person aircraft::getPilot() {
	return A;
}
void aircraft::setCoPilot(person theCo){
	B = theCo;
}

person aircraft::getCoPilot(){
	return B;
}
void aircraft::printDetails() {
	cout << callsign << "\n" << A.getName() << "\n";
	cout << B.getName()<< "\n";
}