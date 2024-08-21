#ifndef COACH_H
#define COACH_H

#include "person.h"
#include <string>

using namespace std;

class Coach:public Person {

 	int serviceLength;                   // the service length of a person
 	int personID;                        // the unique ID of a person
 	static int nextID;
 	public:
 		Coach(string, int); //name-sl
 		Coach();

		int get_salary();

};

#endif //COACH_H
