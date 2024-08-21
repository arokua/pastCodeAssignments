#include <iostream>
#include <string>
#include <vector>
#include "computer.h"
#include "Avalanche.h"
#include "Bureaucrat.h"
#include "Crescendo.h"
#include "FistfullODollars.h"
#include "PaperDoll.h"
#include "ToolBox.h"
#include "referee.h"
#include "RandomComputer.h"
#include "Tournament.h"
#include "stdlib.h"
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

int main() {
    Tournament tt(8);
    tt.myPlayers(takeInput());
    tt.begin();
    cout << tt.getWinner() <<endl;
}
/*
Test if Crescendo refreshs mem after each times it is used
int main() {
  for (int c = 0; c < 50; c+= 5) {
    computer* CR = new Crescendo(c + 9, 2 - c);
    CR->makeMoves();
    vector<char> cc = CR->getMoves();
    cout << CR->totalSteps() <<endl;
    for (int i = 0; i< cc.size(); i++){
      cout << cc[i] << " ";
    }
    cout << endl;
  } 
}
*/