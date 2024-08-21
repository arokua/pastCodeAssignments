#ifndef STAFF_H
#define STAFF_H
#include <iostream>
#include <string>
#include "human.h"
#include "student.h"

using namespace std;

class staff : public human{

  //state variables
  string staffID;
	string staffPassword;
  string accessLevel;             // 2 types: teacher & admin

  public:
		staff();
    staff(string, string, string ); //ID, pass, access lvl

    //behaviours
    void setStaffID(string );              //change this staff's ID
    string getStaffID();                                    //return this staff's ID
    void setStaffPassword(string);   //change this staff's password
    string getStaffPassword();                      //return this staff's password

    string getStaffType() {
      return accessLevel;
    }

    void viewStudentInfo(student *);             //prints out selected student's info
    void setStudentPassword(student * , string ); //reserved for admin type access level
    void createPreRequisites(string );     //reserved for teacher type access level

    ~staff();
};
#endif
