#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

using namespace std;
class animal{
	string name;

	int animalId;
	int volume;

	public:
		animal(string, int);
		void set_name(string);
		virtual string get_name() = 0;

		void set_volume(int);
		int get_volume();

		int get_animalID();
};
#endif //ANIMAL_H