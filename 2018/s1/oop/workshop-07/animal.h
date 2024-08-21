#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

using namespace std;
class animal{
	string race;
	string name;
	static int theId;
	int ownId;

	public:
		animal(string);
		void set_name(string);
		string get_species();
		string get_name();
		int get_ID();
};
#endif //ANIMAL_H