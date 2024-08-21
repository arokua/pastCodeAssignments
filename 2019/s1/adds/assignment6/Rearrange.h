#ifndef REARRANGE_H
#define REARRANGE_H

#include <string>
#include "Individual.h"
#include "Mutator.h"

class Rearrange: public Mutator{
    public:
        Rearrange(); // constructor
        Individual* mutate(Individual*, int); // get the individual whose offspring tobe is mutated
};
#endif