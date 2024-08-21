#ifndef PERSON_H
#define PERSON_H

#include <string>

using namespace std;

class Person {
	string name;                       // the name of a person
 	string occupation;                 // the occupation of a person
 	int salary;                        // the salary of a person; takes only non-negative values
 	int serviceLength;                   // the service length of a person
 	int personID;                        // the unique ID of a person
 	public:
 		Person(string, string, int); //name-occu-sl
 		Person();

 		void set_name(string);
 		string get_name();

 		void set_occupation(string);
 		string get_occupation();

 		void set_salary(int);
 		virtual int get_salary() = 0;

 		int get_personID();

};

#endif //PERSON_H
