#include <string>
#include "staff.h"
#include "student.h"
#include "course.h"

using namespace std;

course::course(string kaka, int num, staff* Who){
	name = kaka;
	capacity = num;
	Lecturer= Who;
}
void course::setNum(int n){
	capacity = n;
}
string course::getCourseName() {
	return name;
}
void course::setLecturer(staff* Mem) {
	Lecturer = Mem;
}
void course::setCourseName(string sf){
	name =sf;
}

string course::getLecturer(){
	return Lecturer->getName();
}
void course::setDuration(int weeks){
	duration = weeks;
}

int course::getCap(){
	return capacity;
}
int course::getDuration(){
	return duration;
}

void course::setAvaliableSemester(int nSem){
	for (int i = 0; i < nSem; i++){
		avaliableSemester[i] = "Semester" + to_string(i + 1 );
		semN +=1;
	}

}

void course::getAvaliableSemester() {
	cout<< name <<" is avaliable in the following semester this year";
	for (int i = 0; i < semN; i++){
		cout <<avaliableSemester[i] <<"\n";
	}
}

void course::addStudent(){
	currentStudentInCourse += 1;
}

void course::removeStudent(){
	currentStudentInCourse -= 1;
}

int course::getStudentAmount() {
	return currentStudentInCourse;
}