#include "animal.h"
#include  <string>

using namespace std;


animal::animal(string aNa, int V){
	name = aNa;
	volume = V;
}

void animal::set_name(string nawa){
	name = nawa;
}

void animal::set_volume(int aV){
	volume = aV;
}

int animal::get_volume(){
	return volume;
}

int animal::get_animalID(){
	return animalId;
}