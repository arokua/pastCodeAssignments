#include "hunter.h"
#include "animal.h"
#include <string>

using namespace std;


hunter::hunter(string ra):animal(ra){
	species = ra;
}

int hunter::numOfKills(){
	return killNo;
}

void hunter::record_kill(string name){
	killList[killNo] = name;
	killNo +=1;

}

string * hunter::get_kills(){
	return killList;
}