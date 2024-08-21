#include <iostream>
#include "human.h"
#include "student.h"
#include "staff.h"
#include "course.h"
#include <vector>
//The program assumes that all courses have no prerequisites
//In this program, admin would have ID starting with A, Lecturer starting with T 

using namespace std;

int main() {
	// Making the student  and staff
	staff Milo("ST1","T54A","Lecturer");
	staff Mi("ST2","T54A","Lecturer");
	staff Mlo("ST3","T54A","Lecturer");

	staff* Mil = &Milo;
	staff* il = &Mi;

	course OOP("OOP",50, Mil);
	course ISE("ISE",50, il); 
	course MMO("Maths IA",50, il);
	course MMB("Maths IB",50, il);

	course CourseList[4] = {OOP, ISE, MMO, MMB};

	Milo.setStaffPassword("Staff123");
	Milo.setName("Jay");


	string userType; // Check if the user is a student, admin or lecturer
	string afterLog1 = "NE";// Store the user chosen option after login
	string afterLog2;// Store the user chosen option after afterLog1
	string afterLog3;// Store the user chosen option after afterLog2
	string afterLog4;// Store the user chosen option after afterLog3
	string back;
	
	student A;
	string newPass;
	string newPassRe; //to type the new pass word a second time for checking
	string inpass;
	string inID;
	student studentList[40] = {};
	studentList[0]= A;



	A.setName("Jones");
	A.setAge(23);
	A.setGender("Male");
	A.setNationality("Australia");
	A.setDOB("2/4/1995");
	A.setStudentPassword("12345");


	while (true ){
		//Login

		cout << "Enter your ID number : "<<endl;
		cin >>inID;
		cout <<"Enter your password: "<<endl;
		cin >> inpass;

		//Check user type
		if (inID.at(0) == '1') {
			userType = "student";
		}


		// ID checking process
		if (userType == "student") {
			while (inID != to_string(A.getStudentID()) or inpass !=A.getStudentPassword()){
				cout <<"Your ID or password is invalid! \n";
				cout << "Enter your ID number : "<<endl;
				cin >>inID;
				cout <<"Enter your password: "<<endl;
				cin >> inpass;

			}

			//Proceediing for student
			A.printStudentInfo();
			while (true){
				//While loop so that when finish with the option, the user can continue

				cout << "\nWhat do you want to do?Enter the option number to proceed. \n";
				cout << "1. Set your password \n";
				cout << "2. Choose a course to enroll\n";
				cout << "3. Exit\n";

				cin >>afterLog1;

				if (afterLog1 == "3"){
					//This  is the go back to login screen
					break;
				}

				else if (afterLog1 == "1"){
					//Set password process
					cout << "Enter your new password:\n";
					cin >>newPass;
					cout << "Please Re enter the password\n";
					cin >>newPassRe;
					while (newPass!=newPassRe){
						cout<<"It doesn't match, please try again!\n";
						cout << "Enter your new password:\n";
						cin >>newPass;
						cout << "Please Re enter the password\n";
						cin >>newPassRe;
					}
					A.setStudentPassword(newPass);
				}

				else if (afterLog1 == "2"){
						cout <<"This is alist of courses that you can choose form, please choose which to add\n";
						for (int m = 0; m< 4; m++){
							cout << CourseList[m].getCourseName()<< "\t";
							cout <<"Teach by " <<CourseList[m].getLecturer()<<"\n";
							
						}
						cin >> afterLog2;
						A.addClass(afterLog2);
						cout <<"You have enrolled in " <<afterLog2 <<".\n";
						
				}

				else {
					cout << "Invalid input, please try again.\n";
				}
			}

		}
	}
}