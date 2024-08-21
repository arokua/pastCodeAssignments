#include <string>
#include <vector>
#include "referee.h"

using namespace std;

referee::referee(){}
char referee::roundResult(char a, char b){
    // Return if a win or lose or tie from a given pair of moves
    if (a == b){
        return 'T';
    }
    
    if ( (a == 'R' && b == 'S') || \
         (a == 'S' && b == 'P') || \
         (a == 'P' && b == 'R')) {
        return 'W';
    }
    return 'L';
}

string referee::matchRe(vector<char> Amoves, vector<char> Bmoves){
    //result of the match as a whole
    string re = "";
    for (int i = 0; i < int(Amoves.size()) - 1; i ++){
        re = re + roundResult(Amoves[i], Bmoves[i]) + " ";
    }
    // Alternative to using an if statement to prevent a whitespace at end of string
    return re + roundResult(Amoves.back(), Bmoves.back());
    
}