#include <vector>
#include <iostream>
#include "FilterGeneric.h"
using namespace std;

FilterGeneric::FilterGeneric() {
}

vector<int> FilterGeneric::filter(vector<int> input){
	return inFilter(input, 0);
}

vector<int> FilterGeneric::inFilter(vector<int> in, int index){
	if (index == int(in.size())){
	//Make a new vector to hold the values of filtered values
    vector<int> re;
    for (int i = 0; i < index; i++){
      if (in[i] != 0){
        re.push_back(in[i]);
      }
    }
    return re;
	}
	//Each recursive calls modify value of in at index using f() then increment index by 1 to move on
	if ( !g(in[index]) ){
    in[index] = 0;
  }
	return inFilter(in, index + 1);
}