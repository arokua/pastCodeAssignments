#ifndef NODE_H
#define NODE_H

class Node {
	private:
		int data;
		Node * next;
	public:
		Node();
    
		//Get and set functions
		void setData(int);
		void setNext(Node *);
		int getDat();
		Node * getNext();
    ~Node();
};
#endif