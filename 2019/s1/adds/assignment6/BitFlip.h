#ifndef BITFLIP_H
#define BITFLIP_H

#include <string>
#include "Individual.h"
#include "Mutator.h"

class BitFlip: public Mutator{
    public:
        BitFlip();//Constructor
        Individual * mutate(Individual*, int); //Take in the individual, create its offspring then mutated that
};
#endif