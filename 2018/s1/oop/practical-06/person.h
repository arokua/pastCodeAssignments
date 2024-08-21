#ifndef PERSON_H
#define PERSON_H

#include <string>

using namespace std;
class person{


	string myName = "00";
	int Salary =0;
	
	
	int Sal = Salary;
	string Na = myName;

    public:
    	person(string ,int);
        void setName(string);
        string getName() ;
        void setSalary(int);
        int getSalary();
};
#endif //PERSON_H