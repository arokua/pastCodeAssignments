#include <stdlib.h>
#include <ctime>
#include "computer.h"
#include "RandomComputer.h"

using namespace std;

char moveFromNum(int n){
    //Given a number 1 to 3, return R or P or S
    if (n < 1 || n > 3){
        return '|';
    }
    if (n == 1){
        return 'P';
    }
    if (n == 2){
        return 'R';
    }
    return 'S';
}
RandomComputer::RandomComputer(int n, int i):computer(n, i){
    //Each time the value in tactic would be choose randomly
    tactic[0] = moveFromNum((rand() % 3) + 1);
    tactic[1] = moveFromNum((rand() % 3) + 1);
    tactic[2] = moveFromNum((rand() % 3) + 1);
    for (int t = 0; t < n; t++){
        tactic.push_back( moveFromNum((rand() % 3) + 1) );
    }
}