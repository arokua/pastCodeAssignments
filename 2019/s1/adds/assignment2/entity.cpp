#include <string>
#include <vector>
#include "entity.h"

using namespace std;
entity::entity(){}

int entity::totalSteps(){
	return m;
}

vector<char> entity::getMoves(){
    return moves;
}