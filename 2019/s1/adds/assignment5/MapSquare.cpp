#include "MapGeneric.h"
#include "MapSquare.h"

using namespace std;

MapSquare::MapSquare(): MapGeneric(){
}

int MapSquare::f(int x){	return x * x;}