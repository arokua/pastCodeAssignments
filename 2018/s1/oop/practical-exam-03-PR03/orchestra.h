#ifndef ORCHESTRA_H
#define ORCHESTRA_H

#include <string>
#include "musician.h"

using namespace std;

class orchestra{
	int size;

	musician firstlist[200]; //array of musicians
	
	int currentMemMo; //Amount of current members
	public:
		orchestra();
		orchestra(int);
		int get_current_number_of_members(); 
		bool has_instrument(string);

		musician * get_members(); 
		bool add_musician(musician );

};

#endif //ORCHESTRA_H
