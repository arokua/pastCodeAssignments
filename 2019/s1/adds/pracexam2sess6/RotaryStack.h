/* 
   code for stack with an additional rotate operation that removes item on the top of the stack and places it on the bottom. 
*/

#ifndef ROTARYSTACK_H
#define ROTARYSTACK_H

#define CAP 8

class RotaryStack{
 public:
  // constructor
  RotaryStack();

  // operators

  void push(int val); // adds val to the top of stack
  int pop(); // removes val from the of stack
  void rotate(); // removes the top of the stack and places it on the bottom. 

 private:
  int content[CAP]; // contents of the queue
  // state variables - depending on implementation you might not use all
  // of these!
  int top; // points to the place where the next item is inserted
  int bottom; // points to the bottom element of the stack
  int count; // number of items in the stack
};

#endif //ROTARYSTACK_H
