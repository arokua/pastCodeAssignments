#include <iostream>
#include "person.h"

#include <string>

using namespace std;

person::person(string a, int b){
	Na = a;
	Sal = b;
}

void person::setName(string na){
    Na = na;
}

void person::setSalary(int n){
    Sal = n;
}

string person::getName(){
    return Na;
}

int person::getSalary(){
    return Sal;
}




