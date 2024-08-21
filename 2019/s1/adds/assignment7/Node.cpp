#include "Node.h"

Node::Node(){
	next = nullptr;
}

void Node::setData(int dat){
	//Set node value
	data = dat;
}

void Node::setNext(Node * ptr){
	//set the node this node is pointing to
	next = ptr;
}

int Node::getDat(){
	//Return own value
	return data;
}
Node * Node::getNext(){
	//Return next node
	return next;
}

Node::~Node(){
	next = nullptr;
	delete next;
}