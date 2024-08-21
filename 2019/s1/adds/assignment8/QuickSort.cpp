#include "Sort.h"
#include "QuickSort.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

QuickSort::QuickSort():Sort(){}
vector<int> subVec(vector<int> v, int start, int end){
    //Create a sub list of a vector
    //Range of a sub vec is [start,end)
    //Value at end is not included
    vector<int> re;
    while (start < end){
        re.push_back(v[start]);
        start++;
    }
    return re;
}
/* merge two vector, for recursion version
vector<int> mergeVector(vector<int> a, vector<int> b){
    //Merge two vectors
    vector<int> t;
    t = a;
    for (int i = 0; i < int(b.size()); i++){
        t.push_back(b[i]);
    }
    return t;
}
*/
vector<int> QuickSort::sorting(vector<int> dat){
    //Quick sort itterative way

    //Small list cases
    if (dat.size() == 1 ){
        return dat;
    }

    if (dat.size() == 2){
        if (dat[0] > dat[1]) return vectorSwapE(dat, 0, 1);
        return dat;
    }
    //The index of the earliest unsorted element
    int indexError = isSorted(dat);

    //Check if the vector is sorted if not then continue swapping
    while (indexError > -1){
        int pivot = max(2, indexError);
        //There are unsorted value before the pivot
        //Do this in case the rest of the vector is sorted from the pivot point
        if (indexError < 2){
            dat = vectorSwapE(dat, 0, 1);
        }
        //Swap elements to left and right of the pivot accordingly
        for (int i = indexError; i < int(dat.size()); i++){
            if (dat[i] <= dat[pivot] && i > pivot) {
                dat = vectorSwapE(dat, pivot, i);
            }else if (dat[i] > dat[pivot] && i < pivot){
                dat = vectorSwapE(dat, i, pivot);
            }
        }
        //Update the current pivot
        indexError = isSorted(dat);
    }
    return dat;
}
void print(vector<int> v){
    //Print a vector out
    for (int i = 0; i < int(v.size()); i++){
        cout << v[i];
        if (i < int(v.size()) - 1) cout << ' ';
    }
    cout <<endl;
}
/*
vector<int> QuickSort::sort(vector<int> v){
    //Do recursion
    if (v.size() == 1 ){
        return v;
    }

    if (v.size() == 2){
        if (v[0] > v[1]) return vectorSwapE(v, 0, 1);
        return v;
    }

    int pivotPos = 2;
    int toCompare = v[pivotPos];
    int final;

    for (int i = 0; i < int(v.size()); i++){
        if (v[i] <= toCompare) {
            v = vectorSwapE(v, pivotPos, i);
            final = i;
        }
        else if (v[i] > toCompare){
            v = vectorSwapE(v, i, pivotPos);
            final = i;
        }
    }
    print( sort( subVec(v, 0, 2 ) ) );
    print( subVec(v, 2, v.size() ) );
    cout <<"_________________________\n";
    v = mergeVector( sort(subVec(v, 0, 2)), sort( subVec(v, 2, v.size() )) );
    return v;
}
*/
vector<int> QuickSort::vectorSwapE(vector<int> v, int a, int b){
    //Swap two elements in a vector
    int temp = v[a];
    v[a] = v[b];
    v[b] = temp;
    return v;
}