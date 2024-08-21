#include "Sort.h"
#include "BubbleSort.h"
#include <vector>

using namespace std;

BubbleSort::BubbleSort() : Sort(){

}

vector<int> BubbleSort::sorting(vector<int> dat){ 
    //Sort the vector by comparing elements 1 by 1
    //Keep sorting while the vector is not fully sorted
    while (isSorted(dat) >= 0 ) {
        //Indices for dat
        int i = 0;
        int j = i + 1;
        bool correct;
        while (j != int(dat.size()) ) {
            correct = dat[i] < dat[j];
            if (!correct){
                int temp = dat[i];
                dat[i] = dat[j];
                dat[j] = temp;
            }
            i++;
            j++;
        }
    }                
    return dat;
}