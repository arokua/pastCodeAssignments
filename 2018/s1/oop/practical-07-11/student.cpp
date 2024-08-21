#include <iostream>
#include <string>
#include "human.h"
#include "staff.h"

using namespace std;

//inialising ID number
int student::ID_counter = 100;

//default contructor - contains nothing
student::student() : human()
{
  studentID = ID_counter;
  ID_counter++;
}

//return student ID
int student::getStudentID()
{
	return studentID;
}

//change student password
void student::setStudentPassword(string aStudentPassword)
{
  studentPassword = aStudentPassword;
}

//return staff password
string student::getStudentPassword()
{
  return studentPassword;
}

//printing student details
void student::printStudentInfo(){
	//Testing purpose
  cout << "ID: "<< studentID <<" " ;
  printInfo() ;
}

//get current amount of courses
int student::getNCourses(){
  if (nCurrentClass == 0){
    return 0;
  }else{
    return nCurrentClass +1;
  }
}

//add a class(course)
void student::addClass(string ClassName){
  if( nCurrentClass < 4){
    currentCourses[nCurrentClass] = ClassName;
    nCurrentClass += 1;
  }else {
    cout<<"You cannot enroll anymore! \n" ;
  }
}

//default destructor
student::~student()
{

}
