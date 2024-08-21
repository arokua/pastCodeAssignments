#include <string>
#include "person.h"
#include "player.h"

using namespace std;

int Player::nextID = 1000;

Player::Player():Person(){

}

Player::Player(string n, int sl, int *list, int m):Person(n,"Player", sl){
	nextID +=1;
}

int searchGame(int x)

int Player::get_salary(){
	if (serviceLength < 20){
		return get_salary();
	}else {
		return 3*get_salary();
	}
}

