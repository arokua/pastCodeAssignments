#ifndef SORT_H
#define SORT_H

#include <vector>

class Sort {    
    public:
        Sort();
        //Pure virtual function for the children to do the sorting
        virtual std::vector<int> sorting(std::vector<int>) = 0;
        //Check if a vector is sorted
        int isSorted(std::vector<int>);
};
#endif