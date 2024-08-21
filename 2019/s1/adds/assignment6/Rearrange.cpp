#include <string>
#include "Individual.h"
#include "Rearrange.h"
#include "Mutator.h"

using namespace std;

Rearrange::Rearrange() :Mutator(){

}
Individual* Rearrange::mutate(Individual * pop, int k){
    //Shift the DNA from k -index to end to the begin of the DNA string
    string DNA = pop->getString();
    int size = DNA.length();
    if (k > size){
        k = k % size;
        if ( k == 0){
           k = size;
        }
    }
    //Mutating the string
    string mutated = DNA.substr(k - 1, DNA.length() - (k - 1) ) + DNA.substr(0, k - 1);
    Individual * child = new Individual(mutated);
    return child;
}