#include "RecursiveBinarySearch.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

RecursiveBinarySearch::RecursiveBinarySearch(){}

string RecursiveBinarySearch::search(vector<int> v, int val, int left,int right){
    //DO binary search, works IFF v is sorted
    int pos = (left + right) / 2;
    if (v[pos] == val){
        return "true";
    }
    if (pos == 0 or pos == right ){
        if (v[0] == val or v[right] == val) {
              return "true";
        }
        return "false";
    }
    if (v[pos] > val){
        return search(v, val, left, pos - 1);
    }
    else if (v[pos] < val){
        return search(v, val, pos + 1, right);
    }
    //Advoid non-return compile error
    return "";    
}