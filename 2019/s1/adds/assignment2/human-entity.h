#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include <vector>
#include "entity.h"

using namespace std;

class human: public entity{
    public:
    human();
    void makeMoves();
};

#endif 