#include <iostream>
#include "Individual.h"
#include "Mutator.h"
#include "BitFlip.h"
#include "BitFlipProb.h"
#include "Rearrange.h"
#include <vector>
#include <string>

using namespace std;

vector<string> takeInput(){
    // split input by spaces
    string in;
    vector<string> pp;
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
            pp.push_back(temp);
            temp ="";
        }
        if (i == len - 1){
            pp.push_back(temp);
        }
    }
    return pp;
}

Individual * execute(Individual * parent, Mutator * m, int k){    
    return m->mutate(parent, k);
}

using namespace std;
int main(){
    //Get the input
    vector<string> inputs = takeInput();
    
    //Intitalise objects
    Individual * a = new Individual(inputs[0]);
    Individual * b = new Individual(inputs[2]);
    BitFlip bf;
    Rearrange re;
    int k1 = stoi(inputs[1]);
    int k2 = stoi(inputs[3]);

    //Print out the output
    Individual * firstMut = execute(a, &bf, k1);
    Individual * secondMut = execute(b, &re, k2);
    cout << firstMut->getString() << " ";
    cout << secondMut->getString() << " ";
    cout << secondMut->getMaxOnes() << endl;

    //Free memory
    delete a; delete b;
    delete firstMut; delete secondMut;
}