#include <string>
#include "Individual.h"
#include <vector>
#include <algorithm>

using namespace std;

Individual::Individual(int l){
    //Create a DNA string of 0s the length of l
    binStr = "";
    for (int i = 0; i < l; i++){
        binStr += '0';
    }
}
Individual::Individual(std::string bs){
    //Accept a string to turn to DNA
    binStr = bs;
}
std::string Individual::getString(){
    return binStr;
}
int Individual::getBit(int pos){
    //Return bit value at  pos index
    return binStr.at(pos) - 48;
}
void Individual::flipBit(int pos){
    //change bit value at pos index 
    pos--;
    //Instead of using if to change the value, 1- 0 = 1 and 1 - 1 is 0. 48 is ASCII of 0
    int newBit =  1 - (binStr.at(pos) - 48);
    string a = to_string(newBit);
    binStr =  binStr.substr(0, pos) + a + binStr.substr(pos + 1, binStr.length() - pos - 1);
}
int Individual::getMaxOnes(){
    // Current length of valid substring
    int currentCons = 0;
    //A vector that store the length of substrings of 1s
    vector<int> chains;
    for (int i = 0; i < int(binStr.length()); i++){
        if (binStr.at(i) == '1'){
            currentCons += 1;
            if ( i ==  int(binStr.length()) - 1 ){
                // In the case of there is no 0 at end of dna
                chains.push_back(currentCons);
            }
        }
        else{
            //End of chain
            if (currentCons > 0){ 
                chains.push_back(currentCons);
                currentCons = 0;
            }
        }
    }
    
    //Sort the vector, final value is the longest substring of 1
    sort(chains.begin(), chains.end());
    return chains[chains.size() - 1];
}

int Individual::getLength(){
    //Return DNA length
    return binStr.length();
}