#include "Mutator.h"
#include "Individual.h"
#include "BitFlip.h"
#include <string>

BitFlip::BitFlip() :Mutator() {

}

Individual * BitFlip::mutate(Individual* I, int k){
    //Create a child of same DNA as I then flip the bit at k position of that child
    //Return a pointer to that child
    int size = I->getString().length();
    // Reduce k to between( 0 and size)
    if (k > size){
        k = k % size;
        if ( k == 0){
           k = size;
        }
    }
    Individual * child = new Individual(I->getString());
    child->flipBit(k);
    return child;
}