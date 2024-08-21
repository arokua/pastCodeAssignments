#ifndef HUNTER_H
#define HUNTER_H

#include "animal.h"
#include <string>

using namespace std;
class hunter: public animal{
	int killNo =0;
	tring 

	public:
		hunter(string);
		void record_kill(string);
		int numOfKills();
		string *get_kills();
};
#endif //HUNTER_H