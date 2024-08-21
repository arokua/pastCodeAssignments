#include <string>
#include "person.h"
#include "coach.h"

using namespace std;

int Coach::nextID = 0;

Coach::Coach():Person(){

}

Coach::Coach(string n, int sl):Person(n, "Coach", sl){
	nextID +=1;
}

int Coach::get_salary(){
	if (serviceLength < 20){
		return get_salary();
	}else {
		return 3*get_salary();
	}
}