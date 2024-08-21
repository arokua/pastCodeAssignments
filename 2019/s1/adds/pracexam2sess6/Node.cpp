#include "Node.h"
#include <iostream>
using namespace std;

Node::Node(int i, Node *n) {
	data = i;
	next = n;
}

