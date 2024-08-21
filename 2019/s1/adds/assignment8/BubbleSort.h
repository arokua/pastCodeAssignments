#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "Sort.h"
#include <vector>

using namespace std;

class BubbleSort :public Sort{
    public:
        BubbleSort();//Constructor
        vector<int> sorting(std::vector<int>);//Do the sort
};
#endif