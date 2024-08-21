#include "animal.h"
#include  <string>

using namespace std;

int animal::theId = 0;

animal::animal(string aSpec){
	race = aSpec;
	theId += 1;
	ownId = theId;
}

void animal::set_name(string nawa){
	name = nawa;
}

string animal::get_name(){
	return name;
}

string animal::get_species(){
	return race;
}

int animal::get_ID(){
	return ownId;
}