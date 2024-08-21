#include "ReduceGeneric.h"
#include "ReduceGCD.h"

ReduceGCD::ReduceGCD():ReduceGeneric(){
};

int ReduceGCD::binOp(int a, int b){
    if (a > b){
        return binOp(b, a);
    }
    if (a == 0){
        return b;
    }
    if (a == 1){
        return 1;
    }
    return binOp(a, b % a);
}