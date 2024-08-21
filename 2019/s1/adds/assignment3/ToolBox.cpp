#include "computer.h"
#include "ToolBox.h"
#include <iostream>

using namespace std;

ToolBox::ToolBox(int n, int i): computer(n, i){
    //Changing tactic
    tactic[0] =  'S';    tactic[1] =  'S';    tactic[2] =  'S';
}