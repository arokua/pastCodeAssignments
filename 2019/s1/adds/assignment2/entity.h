#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

using namespace std;

class entity{
    protected:
    vector<char> moves;
    int m = 0;
    public:
    entity();
    virtual void makeMoves() = 0;
    int totalSteps();
    vector<char> getMoves();
};

#endif 