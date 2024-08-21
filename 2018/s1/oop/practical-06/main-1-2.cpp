#include <iostream>
#include "person.h"

using namespace std;
int main() {
	person A("Bob", 42);
	cout<<"Person: "<< A.getName() << " has salary " << A.getSalary()<< "\n";
	
	A.setName("Billy");
	A.setSalary(99);
	cout<<"Person: "<< A.getName() << " has salary " << A.getSalary()<< "\n";
}
