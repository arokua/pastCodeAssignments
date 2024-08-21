#include <iostream>
#include <vector>
#include "Node.h"
#include "LinkedList.h"
#include <string>

using namespace std;
//Holds the numbers of original nodes from input
static int nNodes;
vector<string> takeInput(){
    // Get input from console
    // Split them by spaces and store to a vector
    string in;
    vector<string> pp;
    std::cout << "";
    getline (std::cin, in);
    //Check whether a string has been meet
    bool metOrder = false;
    int len = in.length(); //length of input
    string temp = ""; //tempoary string
    for (int i = 0; i < len; i++){
        char current = in.at(i);
        if (current != ' '){
            temp += current;
            if ( !isdigit(current) && !metOrder){
                nNodes = pp.size() - 1;
                metOrder = true;
            }
        }
        else{
            pp.push_back(temp);
            temp ="";
        }
        if (i == len - 1){
            pp.push_back(temp);
        }
    }
    nNodes++;
    return pp;
}

int main(){
    //Get input
    vector<string> ins = takeInput();
    //Take in the list of nodes value   
    vector<int> arr; //vector that holds the node values
    for (int i = 0; i < nNodes; i++){
        arr.push_back(stoi(ins[i].c_str()));
    }
    //Make a linked list object using above values
    LinkedList ll(arr,nNodes);
    //Operations to be performed
    string order = ins[nNodes];
    if (order == "AF") ll.addFront(stoi(ins[nNodes + 1].c_str()));
    else if (order == "AE") ll.addEnd(stoi(ins[nNodes + 1].c_str()));
    else if (order == "AP") ll.addAtPosition(stoi(ins[nNodes + 1].c_str()), stoi(ins[nNodes + 2].c_str()));
    else if (order == "DF") ll.deleteFront();
    else if (order == "DE") ll.deleteEnd();
    else if (order == "DP") ll.deletePosition(stoi(ins[nNodes + 1].c_str()));
    else if (order == "S") ll.search(stoi(ins[nNodes + 1].c_str()));
    else if (order == "GI") ll.getItem(stoi(ins[nNodes + 1].c_str()));
    else cout << "Invalid command\n";
    //Print out result
    ll.printItems();
}