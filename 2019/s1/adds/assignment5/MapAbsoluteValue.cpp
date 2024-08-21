#include "MapGeneric.h"
#include "MapAbsoluteValue.h"
#include <algorithm>

using namespace std;

MapAbsoluteValue::MapAbsoluteValue(): MapGeneric(){
}

int MapAbsoluteValue::f(int x){	return max(x, 0 - x);}