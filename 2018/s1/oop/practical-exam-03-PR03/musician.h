#ifndef MUSICIAN_H
#define MUSICIAN_H

#include <string>

using namespace std;

class musician{
	string instrumentList[15]= {}; //the list of total instrument a musican can play
	int amountofInt;//the amount of instrument in the above array

	string instrument;
	string name;
	int expe;

	public:
		musician();
		musician(string, int);
		string get_instrument();
		void addInstrument(string); //Do as func name say
		void setName(string); //Do as func name say
		
		string getName(); // Do as func name say
		int get_experience();

};
#endif //MUSICAN_H