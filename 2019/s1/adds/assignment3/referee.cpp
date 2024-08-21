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

vector<char> referee::match(vector<char> Amoves, vector<char> Bmoves){
    //result of the match as a whole
    vector<char> re;
    for (int i = 0; i < int(Amoves.size()); i ++){
        re.push_back(roundResult (Amoves[i], Bmoves[i]));
    }
    return re;    
}

int referee::result(vector<char> re){
    //Return 0 if tie, 1 if A wins, -1 if B wins
    int v[3] = {0, 0, 0}; //count the ratio of the match result
    for (int i = 0; i < int(re.size()); i ++){
        if (re[i] == 'W'){
            v[0] += 1;
        }else if (re[i] == 'L'){
            v[2] += 1;
        }else{
            v[1] += 1;
        }
    }
    if (v[0] > v[2]){
        return 1;
    }

    if (v[0] < v[2]){
        return -1;
    }
    return 0;
}