#ifndef BITFLIPPROB_H
#define BITFLIPPROB_H

#include <string>
#include "Individual.h"
#include "Mutator.h"

class BitFlipProb: public Mutator{
    public:
        BitFlipProb(); //constructor
        Individual* mutate(Individual*, int); //create a new Individual and mutate the bits randomly
};
#endif