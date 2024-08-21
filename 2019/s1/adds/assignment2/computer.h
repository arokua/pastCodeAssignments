#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include "human.h"

class computer{
    public:
    std::vector<char> moves;
    computer();
    void makeMoves(int);
};

#endif //COMPUTER_H