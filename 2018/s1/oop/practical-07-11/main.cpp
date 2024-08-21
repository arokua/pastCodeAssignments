#include <iostream>
#include <stdlib.h>
#include "human.h"
#include "student.h"
#include "staff.h"


using namespace std;

int main() {

	
	student studA;
	studA.setName("Jones");
	studA.setAge(23);
	studA.setGender("Male");
	studA.setNationality("Australia");
	studA.setDOB("2/4/1995");

	studA.printStudentInfo();
}
