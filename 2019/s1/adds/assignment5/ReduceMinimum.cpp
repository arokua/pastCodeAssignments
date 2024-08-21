#include <algorithm>
#include "ReduceGeneric.h"
#include "ReduceMinimum.h"

using namespace std;
ReduceMinimum::ReduceMinimum():ReduceGeneric(){
};

int ReduceMinimum::binOp(int a, int b){
    return min(a, b);
}