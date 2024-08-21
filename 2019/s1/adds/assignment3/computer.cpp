#include <vector>
#include "computer.h"

using namespace std;

computer::computer(int n, int i) {
    turnNum = 0;
    tactic.reserve(3);
    tactic[0] =  'R';    tactic[1] =  'R';    tactic[2] =  'R'; //The original tactic of using only rocks from prac 2
    
    numMoves = n;
    my_index = i; // index of the player from the input
}
    
void computer::makeMoves() {
    while (numMoves > turnNum) {
        moves.push_back(tactic[turnNum % 3]); // For the 3 last classes that need altrernatively going the same tactic after a while
        turnNum++;
    }turnNum = 0; //refreshe the  mem
}

int computer::totalSteps(){
	return numMoves;
}

vector<char> computer::getMoves(){
    return moves;
}

int computer::id(){
    return my_index;
}