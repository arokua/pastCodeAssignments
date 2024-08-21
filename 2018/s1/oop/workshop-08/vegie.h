#ifndef VEGIE_H
#define VEGIE_H

#include "animal.h"
#include <string>

using namespace std;
class vegie: public animal{
	string typer;
	string yummy;

	public:
		vegie(string);
		void set_favourite_food(string);
		string getFavouriteFood();
};
#endif //VEGIE_H