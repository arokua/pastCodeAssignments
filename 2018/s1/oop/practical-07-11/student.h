#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
#include "human.h"


using namespace std;
class student : public human{

 	static int ID_counter;
 	int studentID;
 	string studentPassword;
 	int nCurrentClass = 0;

 	string currentCourses[4] ={};
    string passedCourses[40];


    public:
		student() ;
		student(string);
	    
	    void addClass(string className);
	    int getStudentID(); 
	    int getNCourses();
	    void setStudentPassword(string aStudentPassword);   //change this student's password
	    string getStudentPassword();                      //return this student's password
	    void printStudentInfo(); 
	                                       //print student info

	    ~student();
};
#endif
