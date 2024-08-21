#include "Node.h"
#include "LinkedList.h"
#include <vector>
#include <iostream>
#include <limits>

using namespace std;
//size of the linked list
static int s;
LinkedList::LinkedList(){
    //Constructor with empty head
    head = NULL;
    s = 0;
}
LinkedList::LinkedList(vector<int> a, int n):LinkedList(){
    //Create a list from a given array
    for (int i = n - 1; i > -1; i--){
        addFront(a[i]);
    }
}

//Adding 
void LinkedList::addFront(int nI){
    //Add a new node to the begining of list
    s++; 
    //head ref , use to advoid segfault
    Node ** hf = &head;
    //Create a new node object
    Node * newbie = new Node();
    newbie->setData(nI);
    //Point to the one head is pointing to
    newbie->setNext(*hf);
    //Change the pointer head is pointing to this new node
    *hf = newbie;
}

void LinkedList::addEnd(int nI){
    //Add a new node to the end of list
    s++;
    //head ref , use to advoid segfault
    Node ** hf = &head;
    //Create a new node object
    Node * newbie = new Node();
    newbie->setData(nI);
    //At to the end so new node points to nothing
    newbie->setNext(NULL);
    //Incase the list is currently empty
    if (*hf == NULL){
        *hf = newbie;
    }
    //Else
    //Get the last node in the current list
    Node * last = *hf;
    while (last->getNext() != NULL){
        last = last->getNext();
    }
    //Newbie is now the last node of the list
    last->setNext(newbie);
}

void LinkedList::addAtPosition(int pos, int nI){
    //Add a new node to the given position
    if (pos < 1) {
        addFront(nI);
        return; // Stop the function since adding is complete
    }
    if (pos > s) {
        addEnd(nI);
        return; // Stop the function since adding is complete
    }
    //head ref , use to advoid segfault
    Node ** hf = &head;

    //The node before pos
    Node * now = (*hf);
    //Create a new node object
    Node * newbie = new Node();
    newbie->setData(nI);
    while (pos > 2){
        now = now->getNext();
        pos--;
    }
    newbie->setNext(now->getNext());
    now->setNext(newbie);
    s++;
}

//Removing

void LinkedList::deleteFront(){
    //Delete the first node
    //If the list is empty then exit
    if (s == 0){
        return;
    }
    //head ref , use to advoid segfault
    Node ** hf = &head;
    Node * temp = (*hf);    
    (*hf) = temp->getNext();
    delete temp;
    s--;
}

void LinkedList::deleteEnd(){
    //Delete the final node
    //If the list is empty then exit
    if (s == 0){
        return;
    }
    //head ref , use to advoid segfault
    Node ** hf = &head;
    //The node after hf
    Node * temp = (*hf);
    while (temp->getNext() != NULL){
        if (temp->getNext() != NULL){
            break;
        }
        temp = temp->getNext();
    }
    s--;
}

void LinkedList::deletePosition(int pos){
    //Delete the final node

    //Invalid position given
    if (pos < 1 or pos > s) {
        cout << "outside range\n";
        return;
    }
    
    if (pos == 1) {
        deleteFront();
        return;
    }
    //Reduce size by 1
    s--;
    //head ref , use to advoid segfault
    Node ** hf = &head;
    Node * temp = *(hf);
    //Get the node that points to the node at pos
    for (int i =1;i < pos - 1; i++){
        temp = temp->getNext();
    }
    Node * afterP = (temp->getNext())->getNext();
    free(temp->getNext());
    temp->setNext(afterP);     
}

void LinkedList::printItems(){   
    //Print data values of all current nodes in the list
    if (head == NULL){
        return;
    }
    //Head reference
    Node ** hf = &head;
    Node * now = (*hf);

    vector<int> out;
    int size = 1;
    out.push_back(now->getDat());
    while (now->getNext() != NULL){
        now = now->getNext();
        out.push_back(now->getDat() );
        size++;
    }
    for (int v = 0; v  < size; v++){
        cout << out[v] << " ";
    }cout <<endl;
}

int LinkedList::search(int item){
    /*Print out the position of a node that contains a given 
      value if exist, else print 0 */
    int pos = 1;
    Node * temp = *(&head);
    while (temp != NULL){
        if (temp->getDat() == item){
          cout << pos <<" ";
          return pos;
        }
        temp = temp->getNext(); 
        pos++;
    }
    cout << "0 ";
    return 0;
}

int LinkedList::getItem(int p){
    //Print out node value at postion p, int_max if out of range
    Node * temp = *(&head);
    if (p < 1 ) {
        cout << numeric_limits < int >::max() <<" ";
        
    }
    int pos = 1;
    while (temp != NULL){
        if (pos == p){
          cout << temp->getDat() <<" ";
          return temp->getDat();
        }
        temp = temp->getNext(); 
        pos++;
    }
    cout << numeric_limits < int >::max() <<" ";
    return numeric_limits < int >::max();
}

//List destructor
LinkedList::~LinkedList(){
    //Delete all remaining nodes
    while (s > 0){
        deleteFront();
    }
}