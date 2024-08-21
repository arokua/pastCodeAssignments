#include "Node.h"

#ifndef LINKEDLIST
#define LINKEDLIST

class LinkedList {
public:
	LinkedList();
	LinkedList(int*, int);
    void printItems();
    void duplicateElements();

private:
    Node * head;
};

#endif //LINKEDLIST
