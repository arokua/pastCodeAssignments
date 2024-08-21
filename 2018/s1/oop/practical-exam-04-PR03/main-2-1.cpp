#include <iostream>
#include <string>
#include "person.h"
#include "coach.h"

using namespace std;

int main(){
	Person *A;
	A = new Coach("Hedge", 10);
	cout << A->get_occupation() << "\n";
}