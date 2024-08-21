#ifndef PLAYER_H
#define PLAYER_H

#include "person.h"
#include <string>

using namespace std;

class Player:public Person {

 	int serviceLength;                   // the service length of a person
 	int personID;                        // the unique ID of a person
 	static int nextID;

 	public:
 		Player(string n, int, int*, int); //name-sl
 		Player();

 		int searchGame(int);

		int get_salary();

};

#endif //PLAYER_H
