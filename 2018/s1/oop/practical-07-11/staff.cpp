#include <iostream>
#include <string>
#include "human.h"
#include "staff.h"
#include "student.h"

using namespace std;

//default contructor - contains nothing
staff::staff(){

}

//alternative contructor - contains ID, password, and access level
staff::staff(string aStaffID, string aStaffPassword, string aStaffAccessLevel):human()
{
	staffID = aStaffID;
	staffPassword = aStaffPassword;
  accessLevel = aStaffAccessLevel;
}

//change staff ID
void staff::setStaffID(string aStaffID)
{
  staffID = aStaffID;
}

//return staff ID
string staff::getStaffID()
{
	return staffID;
}

//change staff password
void staff::setStaffPassword(string aStaffPassword)
{
  staffPassword = aStaffPassword;
}

//return staff password
string staff::getStaffPassword()
{
  return staffPassword;
}

//prints a students details
void staff::viewStudentInfo(student *aStudent){
  aStudent->printStudentInfo();
}

//changes a students password - admin only
void staff::setStudentPassword(student *aStudent, string aStudentPassword){
  aStudent->setStudentPassword(aStudentPassword);
}

//default destructor
staff::~staff()
{

}
