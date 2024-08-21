#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <string>

class Individual{
    private:
        std::string binStr;
    public:
        Individual(int l);
        Individual(std::string);
        std::string getString();
        int getBit(int);
        void flipBit(int);
        int getMaxOnes();
        int getLength();
};
#endif