#include "entity.h"
#include "human.h"
#include <iostream>

using namespace std;

human::human(): entity(){}

void human::makeMoves(){
    string ss;
    cout <<"";
    getline(cin, ss);
    int l = int(ss.length());
      for (int i = 0; i < l; i++){
          if (ss.at(i) == ' '){
              m = atoi(ss.substr(0, i).c_str());
              break;
          }
      }
      for (int j = to_string( m ).length() + 1; j < l; j += 2){
          moves.push_back(ss.at(j));
      }
}