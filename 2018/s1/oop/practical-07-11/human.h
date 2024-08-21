#ifndef HUMAN_H
#define HUMAN_H
#include <string>
#include <iostream>

using namespace std;
class human {
	string name;
	int age;
	string gender;
	string DateOfBirth; //Please use '/' to seperate the day,month and year
	string Nationality;

	public:
		human();

		void setName(string);
		string getName();

		void setAge(int);
		int getAge();

		void setDOB(string);
		string getDOB();

		void setGender(string);
		string getGender();

		void setNationality(string);
		string getNationality();

		void printInfo();
};
#endif //HUMAN_H

