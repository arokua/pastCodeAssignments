#include <iostream>
#include "person.h"
#include "aircraft.h"

using namespace std;
int main() {

	person A("Bob", 42);
	person B("notABob", 200);
	person C("JustJoe", 1);

	aircraft QuaA("What is a callsign?",A, B);
	QuaA.setPilot(C);
	QuaA.setCoPilot(A);

}
