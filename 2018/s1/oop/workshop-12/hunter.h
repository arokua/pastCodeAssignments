#ifndef HUNTER_H
#define HUNTER_H

#include "animal.h"
#include <string>

using namespace std;
class hunter: public animal{
	int kills =0;
	static int nextID;
	int animalID;


	public:
		hunter(string,int);
		void set_kills(int);
		int get_kills();

		string get_name();
};
#endif //HUNTER_H