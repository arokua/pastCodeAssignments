#include <vector>
#include "human.h"
#include "computer.h"

using namespace std;

computer::computer() {    }
    
void computer::makeMoves(int n) {
    while (n > 0) {
        moves.push_back('R');
        n -= 1;
    }
}