#ifndef MUTATOR_H
#define MUTATOR_H

#include <string>
#include "Individual.h"

class Mutator{
    public:
        Mutator();
        virtual Individual * mutate(Individual*, int) = 0;
};
#endif