#ifndef COMPUTER_H
#define COMPUTER_H

#include "vector"

class computer{
    protected:
    std::vector<char> moves;
    int numMoves;
    int my_index;
    int turnNum ;
    std::vector<char> tactic;
    public:
    computer(int, int);
    void makeMoves();
    int totalSteps(); //return numMoves
    std::vector<char> getMoves();
    int id(); //return the index
};

#endif