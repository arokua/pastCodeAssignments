#include "Mutator.h"
#include "Individual.h"
#include "BitFlipProb.h"
#include "stdlib.h"
#include <iostream>
#include <string>
using namespace std;

BitFlipProb::BitFlipProb() :Mutator() {

}

Individual * BitFlipProb::mutate(Individual * I, int k){
    //Randomly flipped a bit of a child of I at some i positions (1 <= i <= k)
    Individual * child = new Individual(I->getString());
    //Trigger number
    int choose = rand() % k;
    /*since the chance that a bit get flip is 1 / k, choose a random number with that chances as the trigger
    If when the next random number is equal to trigger, the bit at that instance will be flipped */
    for (int i = 0; i < k; i++){
        int now = rand() % k;
        if (now == choose){
            child->flipBit(i);
        }
    }
    return child;
}