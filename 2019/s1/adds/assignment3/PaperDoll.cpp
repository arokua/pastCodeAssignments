#include "computer.h"
#include "PaperDoll.h"
#include <iostream>

using namespace std;

PaperDoll::PaperDoll(int n, int i): computer(n, i){
    //Changing tactic
    tactic[0] =  'P';    tactic[1] =  'S';    tactic[2] =  'S';
}