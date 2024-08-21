#include "hunter.h"
#include "animal.h"
#include <string>

using namespace std;

int hunter::nextID = 1000;
hunter::hunter(string hNa, int hV):animal(hNa, hV){
	name = hNa;
	set_name(hNa);
	animalID = nextID;
	nextID +=1;

	
}
void hunter::set_kills(int K){
	kills = K;
}
int hunter::get_kills(){
	return kills;
}

string hunter::get_name(){
	return "Hunter: " + name;
}