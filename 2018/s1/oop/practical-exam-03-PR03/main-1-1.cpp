#include <iostream>
#include "musician.h"

using namespace std;

int main(){
	musician A("Piano", 5);
	A.setName("moze");
	cout<< A.getName()<< " use "<<A.get_instrument() << " " << A.get_experience() << "\n";
}