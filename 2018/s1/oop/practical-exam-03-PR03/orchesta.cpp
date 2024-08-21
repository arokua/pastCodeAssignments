#include <string>
#include "musician.h"
#include "orchestra.h"

using namespace std;

orchestra::orchestra(){
	size = 0;
	currentMemMo = 0;
	
}

orchestra::orchestra(int amount){
	size = amount;
	currentMemMo = 1;
}
int orchestra::get_current_number_of_members(){
	return currentMemMo;
}


bool orchestra::has_instrument(string instrument){
	for (int i =0; i< currentMemMo; i++){
		if (instrument == firstlist[i].get_instrument()){
			return true;
		}else{
			return false;
		}
	}
}

musician * orchestra::get_members(){
	return firstlist;
}

bool orchestra::add_musician(musician new_musician){
	if (currentMemMo < size){
		firstlist[currentMemMo-1] = new_musician;
		currentMemMo +=1;
		return true;
	}
	else{
		return false;
	}
}
