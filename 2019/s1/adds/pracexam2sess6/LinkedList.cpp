#include "LinkedList.h"
#include <iostream>
using namespace std;

//default constructor
LinkedList::LinkedList() {
	head = nullptr;
 }

//the constructor that takes an array of positive size
LinkedList::LinkedList(int* arr, int length) {
    if (length==0)
    {
        head= nullptr;
        return;
    }
    Node * newNode= new Node(arr[0], nullptr);
    head= newNode;
    for(int i=1; i<length; i++)
    {
        Node * nextNewNode= new Node(arr[i], nullptr);
        newNode->next= nextNewNode;
        newNode=nextNewNode;
    }
    return;
}

//the print function
void LinkedList::printItems() {
    if(head != nullptr)
    {
        Node* nextNode = head;
        while (nextNode != nullptr)
        {
            std::cout << nextNode->data << ' ';
            nextNode = nextNode->next;
        }
        std::cout << std::endl;
    }
    return;
}

//to be implemented
void LinkedList::duplicateElements(){
    if(head != nullptr)
    {   
        //if head is not empty then there is at least one node in the list
        // node that is currently being point at
        Node* currentNode = head;       
        
        while (currentNode != nullptr)
        {
            //Create a new node with the same value as the current node
            //This node point to the node being pointed to by the current node
            Node* dupNode = new Node(currentNode->data, currentNode->next );
            //Current node then points to the new node
            currentNode->next = dupNode;
            //Update current node to its original next node
            currentNode = dupNode->next;
        }
    }
    return ;
}



