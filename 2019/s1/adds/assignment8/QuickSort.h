#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "Sort.h"
#include <vector>
class QuickSort : public Sort{
    public:
    QuickSort();//Constructor
    std::vector<int> sorting(std::vector<int>);//Sort
    std::vector<int> vectorSwapE(std::vector<int>, int, int);//Return a vector with swapped elements
    //std::vector<int> sort(std::vector<int>); //Recursive version, in progress
};
#endif