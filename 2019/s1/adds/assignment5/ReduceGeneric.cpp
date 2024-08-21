#include <vector>
#include "ReduceGeneric.h"

using namespace std;
ReduceGeneric::ReduceGeneric(){

}
int ReduceGeneric::reduce(vector<int> v){
	return inReduce(v, v[0], 1);
}
int ReduceGeneric::inReduce(vector<int> v, int now, int index){
	// Return the result of the final comparision
	if (index == int(v.size())){
		return now;
	}//compare the value of now and at the index of v, return the result
	return inReduce(v, binOp(now, v[index]), index + 1);
}