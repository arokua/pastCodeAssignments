#include <iostream>
#include "MapGeneric.h"
#include "MapTriple.h"
#include "MapSquare.h"
#include "MapAbsoluteValue.h"
#include "FilterGeneric.h"
#include "FilterOdd.h"
#include "FilterForTwoDigitPositive.h"
#include "ReduceGeneric.h"
#include "ReduceMinimum.h"
#include "ReduceGCD.h"

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


int main(){
  //get input
  vector<int> input = takeInts();
  // Creating neccessary objects
  MapAbsoluteValue MAV;
  MapTriple M3;
  FilterForTwoDigitPositive tdd;
  FilterOdd FO;
  ReduceMinimum rmin;
  ReduceGCD gc_list;
  //Mapping
  vector<int> L1 = M3.map(MAV.map(input));
  //Create L2
  vector<int> L2 = tdd.filter(FO.filter(L1));
  //Print out the reduced values of L2
  cout << rmin.reduce(L2)<<" "<<gc_list.reduce(L2) <<endl;
}