#include "Sort.h"
#include <vector>

using namespace std;
Sort::Sort(){}

int Sort::isSorted(vector<int> v){
    //return the first index of an unsorted number, otherwise return -1
    for (int i = 0; i < int(v.size()) - 1; i++){
        if ( v[i] > v[i + 1]) return i;
    }
    return -1;
}