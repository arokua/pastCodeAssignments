#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <vector>
#include <vector>

class LinkedList{
	private:
		Node * head;
	public:
		LinkedList();//Empty constructor
		LinkedList(std::vector<int>, int); //With a given array
		//Adding 
		void addFront(int);//To the front
		void addEnd(int);// To the end
		void addAtPosition(int, int); //At a given position
		//Removing
		void deleteFront();//Remove first node
		void deleteEnd();//Remove last node
		void deletePosition(int); //Remove node as a position
		//Display and find
		int search(int); //Search a node base on its value
		int getItem(int); //Get a node base on position
		void printItems(); //Print out all node from head
    	~LinkedList();
};
#endif