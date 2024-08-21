#ifndef HUMAN_H
#define HUMAN_H

#include <vector>

class human{
    int numMoves = 0;
    public:
    std::vector<char> moves;
    human();
    void makeMoves();
    int totalSteps();
    ~human();
};

#endif 