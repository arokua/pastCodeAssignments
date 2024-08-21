#ifndef COURSE_H
#define COURSE_H

#include <string>
#include "staff.h"

using namespace std;
class course {
	string name;
	int capacity;
	int currentStudentInCourse = 0;
	staff* Lecturer;
	int duration; // number of months
	string avaliableSemester[3];
	int semN =0;

	public:
		course(string, int, staff*); // Course name, num of students, lecturer
		void setNum(int); // set Capacity
		
		void setCourseName(string);
		string getCourseName();

		void setLecturer(staff*);
		string getLecturer();
		
		void setDuration(int);

		void addStudent();
		void removeStudent(); // For when student drop this course
		int getStudentAmount();

		int getCap();
		int getDuration();

		void setAvaliableSemester(int);
		void getAvaliableSemester();

};
#endif //COURSE_H