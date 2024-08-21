#include "computer.h"
#include "Bureaucrat.h"
#include <iostream>

using namespace std;

Bureaucrat::Bureaucrat(int n, int i): computer(n, i){
    tactic[0] =  'P';    tactic[1] =  'P';    tactic[2] =  'P';
}