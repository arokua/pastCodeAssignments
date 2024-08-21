#include <iostream>
#include <string>
#include <vector>
#include "human.h"
#include "stdlib.h"

using namespace std;

human::human(){
    
}

void human::makeMoves(){
    //Get input of the total number of moves from users and what each move is
    string in;
    cout <<"";
    getline(cin, in);
    int l = int(in.length());
    //Get the total moves
    for (int i = 0; i < l; i++){
        if (in.at(i) == ' '){
            numMoves = atoi(in.substr(0, i).c_str());
            break;
        }
    }
    //Add the moves to the vector array for later use
    for (int j = to_string(numMoves).length() + 1; j < l; j += 2){
        moves.push_back(in.at(j));
    }
}

int human::totalSteps(){
    return numMoves;
}

human::~human(){

}