#include "human.h"
#include "computer.h"
#include "referee.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    human A;
    referee R;
    computer Bot;
    A.makeMoves();
    Bot.makeMoves(A.totalSteps());
    cout << R.matchRe(A.moves, Bot.moves) << endl;
}