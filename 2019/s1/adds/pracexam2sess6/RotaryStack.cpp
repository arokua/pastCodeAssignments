#include <iostream>
#include "RotaryStack.h"
#include <algorithm>
using namespace std;

bool isEmpty(int arr[] , int n){
	//check if an array of size n is empty
	for (int i = 0; i < n ;i++){
		if (arr[i] > 0 && arr[i] < 32367) return false;
	}
	return true;
}
RotaryStack::RotaryStack(){
	count = 0;
	//If the list is not empty, bottom points to CAP - 1
	if (!isEmpty(content, CAP))	bottom = CAP - 1;
	top  = 1;
}

void RotaryStack::push(int v){
	if (count < CAP - 1){
		content[top] = v;
		count++;
	}
	top++;
	top = top % CAP;
}

int RotaryStack::pop() {
	if (isEmpty(content, CAP)) return -1;
	content[top] = 0;
	count--;
	top --;

	if (top>= CAP) top = top % CAP;
	return top;
}

void RotaryStack::rotate(){
	int now = pop();
	content[bottom - 1] = content[now];
	bottom = CAP - bottom % CAP - 1;
}