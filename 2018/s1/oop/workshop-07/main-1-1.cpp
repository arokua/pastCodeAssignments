#include <iostream>
#include "animal.h"
#include  <string>

using namespace std;

int main(){
	animal e1("Elephant");
	e1.set_name("Hanyball");

	animal e2("Cheetah");
	e2.set_name("Jalily");

	cout << e1.get_name() << " " << e1.get_species() << " "<< e1.get_ID()<< "\n";
	cout << e2.get_name() << " " << e2.get_species() << " "<< e2.get_ID()<< "\n";
}