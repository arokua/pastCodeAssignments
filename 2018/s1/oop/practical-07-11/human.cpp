#include <string>
#include "human.h"

using namespace std;
human::human(){
	
}

void human::setName(string nawa) {
	name = nawa;
}
string human::getName() {
	return name;
}

void human::setAge(int A){
	age = A;
}
int human::getAge(){
	return age;
}

void human::setDOB(string dob){
	DateOfBirth = dob;
}
string human::getDOB(){
    return DateOfBirth;
}

void human::setGender(string gen){
	gender = gen;
}
string human::getGender(){
	return gender;
}

void human::setNationality(string b){
	Nationality = b;
}
string human::getNationality(){
  return Nationality;
}

void human::printInfo(){
	//Testing purpose
	cout << "Name: "<< name << ". Gender: " << gender;
	cout << ". Date of birth: "<< DateOfBirth << ". Age: "<< age;
	cout << ". Nationality: " << Nationality <<"\n" ;
}