#include "RotaryStack.h"


#include<iostream>
using namespace std;

int main(){

  // setup a stack object and a val to store pops
  RotaryStack s;
  int tmp;

  // these operations can't help
  cout << s.pop() << " " << endl;

  // now push  a few times
  s.push(1);
  s.push(2);
  s.push(3);
  s.push(4);
  s.push(5);
  s.push(6);



  // now pop  a few times
  cout << s.pop() << endl;
  cout << s.pop() << endl;
  // couple of rotations
  s.rotate();
  s.rotate();


  
  // now pop  a few times
  cout << s.pop() << endl;
  cout << s.pop() << endl;
  cout << s.pop() << endl;
  cout << s.pop() << endl;
  cout << s.pop() << endl;
  cout << s.pop() << endl;

  
  
}
