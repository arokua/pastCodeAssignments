#include <iostream>
#include <vector>
#include <string>
#include "QuickSort.h"
#include "BubbleSort.h"
#include "Sort.h"
#include "RecursiveBinarySearch.h"
using namespace std;

vector<int> takeInts(){
    // take the list of strings from input and store to vector
    string in;
    vector<int> pp;
    std::cout << "";
    getline (std::cin, in);
      
    int len = in.length(); //length of input
    string temp = ""; //tempoary string
    for (int i = 0; i < len; i++){
        char current = in.at(i);
        if (current != ' '){
          temp += current;
        }
        else{
            pp.push_back(stoi(temp.c_str()));
            temp ="";
        }
        if (i == len - 1){
            pp.push_back(stoi(temp.c_str()));
        }
    }
    return pp;
}

void print_vector(vector<int> v){
    for (int i = 0; i < int(v.size()); i++){
        cout << v[i];
        if (i < int(v.size()) - 1) cout << ' ';
    }
    cout <<endl;
}

int main() {
    QuickSort qs;
    RecursiveBinarySearch rbs;
    vector<int> t = takeInts();    
    t = qs.sorting(t);
    cout << rbs.search(t, 1, 0, t.size() - 1) << " ";
    print_vector(t);
    return 1;
}