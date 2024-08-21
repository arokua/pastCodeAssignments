#include <vector>
#include "MapGeneric.h"

using namespace std;

MapGeneric::MapGeneric() {
}

vector<int> MapGeneric::map(vector<int> input){
	return inMap(input, 0);
}

vector<int> MapGeneric::inMap(vector<int> in, int index){
	if (index == int(in.size())){
		//If this function has go through the whole list, which means 
		//finished modifying the values of the vector, then return said vector
		return in;
	}
	//Each recursive calls modify value of in at index using f() then increment index by 1 to move on
	in[index] = f(in[index]);
	return inMap(in, index + 1);
}