#include "musician.h"
#include <string>

using namespace std;

musician::musician(){
	expe = 0;
	instrument = "none noted";
}


musician::musician(string tol, int xp){
	instrument = tol;
	instrumentList[0] = instrument;
	expe = xp;
	
}

void musician::addInstrument(string naln){
	amountofInt +=1;
	instrumentList[amountofInt] = naln;
}

string musician::get_instrument(){
	return instrument;
}

int musician::get_experience(){
	return expe;
}

void musician::setName(string waw){
	name = waw;
}

string musician::getName(){
	return name;
}

