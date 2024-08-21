#include<iostream>
using namespace std;

/* General instructions: Please modify this file and submit the modified one
   via svn and then websubmission (under the entry "pracExam"). No design
   documents are needed.
*/

struct Node {
    int data;
    Node* next;
};

/* Task 1: Implement the following function for adding a new node to the 
   front of the given list.

   input   Nodes* head: a head pointer to a list
           int val: an integer that represent the value of the new
                    node
   return  the head pointer of the new list after the insertion

   Example: add a node of value 9
            before  HEAD->1->2->3->NULL
            after   HEAD->9->1->2->3->NULL

 
*/

Node* add(Node* head, int val){
	Node ** hr = &head;
	Node * temp = new Node;
	temp->data = val;
	temp->next = (*hr);
	(*hr) = temp;
	return (*hr);

}

/* Task 2: Implement the following function for printing the elements
   in odd position of the given list. Assume the head node is defined 
   to be in position 1.

   input   Nodes* head: a head pointer to a list

   return  void
          
   output  The elements in odd position of the given list

   Example: input    HEAD->1->2->3->9->12->NULL
            output   HEAD->1->NA->3->NA->12->NULL

 
*/

void printOdd(Node* head){
	int now = 1;
	Node * temp ;
	while (head){
		temp = head;
		if (now % 2 == 1)	cout << temp->data;
		else cout << "NA";
		//If the temp is not last node then temp still point to something
		if (head->next != NULL) cout <<"->";		

		head = head->next;
		now++;
	}
	cout <<endl;

}

/* Task 3: Implement the following function for deleting the nodes in
   between Node n1 and Node n2.

   input   Nodes* n1: a pointer to a node in a list
           Nodes* n2: a pointer to a node in the same list

   return  void

   Example: input   n1 points to the 1st node 
                    n2 points to the 4th node

            before  HEAD->1->2->3->9->12->NULL

            after   HEAD->1->9->12->NULL

   
*/

void clear(Node* n1, Node* n2){
	//Node * temp = new Node;
	/*if (n1 != NULL) {
		while (n1->next != n2 && n1 != NULL){
			cout <<"break!\n";

			if (n1->next != n2) n1 = n1->next;
		}
	}*/

}

// You are not supposed to change the main function
int main() {

    Node* head = NULL;
    Node *p4, *p7;
    int test;
    cin >> test;

    for(int i = 1; i < 10; i++) {
        head = add(head, i);
        if (i==4) p4 = head;
        if (i==7) p7 = head;
    }
    // at this point, we have created the following list: HEAD->9->8->7->6->5->4->3->2->1->NULL
    // p4 now points to node 4 (the node containing 4); p7 now points to node 7 (the node containing 7)

    clear(p4, p7);
    // between p4 and p7, there are 2 nodes. Delete both of them.
    // The resulting list is HEAD->9->8->7->4->3->2->1->NULL

    //You can uncomment this line to test.
    //the output should be: HEAD->9->NA->7->NA->3->NA->1->NULL
    //Please remember to comment this line out before submitting
    //printOdd(head);
    

    head = add(head, 12);
    head = add(head, 15);
    // at this point, the list is: HEAD->15->12->9->8->7->4->3->2->1->NULL

    clear(head, p7);
    // between p7 and head, there are 3 nodes (12, 9 and 8). Remove them all.
    // The resulting list is HEAD->15->7->4->3->2->1->NULL
    printOdd(head);
    // the output should be: HEAD->15->NA->4->NA->2->NA->NULL


    /*free all nodes
    Node* tmp;
    while (head) {
        tmp = head;
        head = head->next;
        delete tmp;
    }*/
    return 0;
  
}
