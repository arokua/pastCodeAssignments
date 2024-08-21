#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> takeInput(){
    // take the list of strings from input, split them by space and store to vector
    string in;
    vector<string> pp;
    std::cout << "";
    getline (std::cin, in);
      
    int len = in.length(); //length of input
    string temp = ""; //tempoary string
    for (int i = 0; i < len; i++){
        char current = in.at(i);
        if (current != ' '){
          temp += current;
        }
        else{
            pp.push_back(temp);
            temp ="";
        }
        if (i == len - 1){
            pp.push_back(temp);
        }
    }
    return pp;
}
/*
class Node {
public:
    string val;
    Node * next;
    Node(string v){
        this->val = v;
        this->next = NULL;

    }
};

class LinkedList{
private:
    int size;
public:
    void make(){
        size = 0;
    }

    Node * add(Node* r, string data){
    //Add a new node to the end of the list
        if (r == NULL){
            r = new Node(data);
            size++;
        }else{
            r->next = add(r->next, data);
        }
    return r;
    }

  Node * deleteNode(Node * r, string data){
      if (r == NULL) return r;
      if (r->val != data) r->next = deleteNode(r->next, data);
      else{
          size--;
          return r->next;
      }
      return r;

  }
    void print(Node * start){
        while (start != NULL){
            cout << start->val <<" ";
      start = start->next;
        }cout <<endl;
    }

};
*/
class HashTable {
    private:  
    string status[26]; // Status of each slot
    string value[26]; //Value inside
    int fullness = 0;
    public:
    HashTable(){
        //Make a new table
        for (int i = 0; i < 26; i++){
            status[i] = "never used";
            value[i] = "None";
        }
    }
    bool  isFull(){
        return (fullness == 25);
    }
    int getHashValue(string word){//Get the hash value of a given word
        //Convert last character to int for easier indexing
        return int(word.back()) - 97;
    }

    int find(string key){
        //Function to return the slot number of a key if it exists, otherwise return -1
        int keyHash = getHashValue(key);
        //Fresh slot
        if (status[keyHash] == "never use") return keyHash;
        if (isFull()) return -1;
        //The first place taken, so go to next slots
        for (int i = keyHash; i < keyHash + fullness + 1; i++){
            if (value[i % 26] == key) return i % 26;            
        }
        return -1;
    }

    void insert(string key){
        if (isFull()) return; //Out of slots
        int index = find(key);
        if (index != -1) return; //Value existed, exit
        else{
            //Start finding an empty slot to insert 
            index = max(index, getHashValue(key));
            for (int i = index; i < index + fullness + 1; i++){
                int current_slot = i % 26 ;
                string current_status = status[current_slot];
                if (current_status != "occupied"){
                    //Found an empty slot
                    value[current_slot] = key; //Update key
                    status[current_slot] = "occupied"; //Change status
                    fullness++;
                    break; //Terminate after inserting
                }
            }
        }
    }
    void deleteNode(string key){
        //Delete a value from a slot if it exists
        //Check existence
        int index = find(key);
        if (index==-1){
            //Not in table, exit
        }else {
            //Start updating value
            value[index] = "None";
            status[index] = "tombstone";
            fullness--;// Decrease total element
        }
    }

    void printTable(){
        for (int i = 0; i < 26; i++){
            if (value[i] != "None") cout << value[i] <<" ";
        }cout <<endl;
    }
};

int main(){
    //Make a new table
    HashTable T;
    //Get and store inputs
    vector<string> cmds = takeInput();
    for (int i = 0; i < int(cmds.size()); i++){
        //Current command for the table
        string thisOrder = cmds[i];
        //Add or del
        char com = thisOrder.at(0);
        //Associated value
        string key = thisOrder.substr(1, int(thisOrder.length()) - 1);
        if (com == 'A'){
            T.insert(key);
        }else {
            T.deleteNode(key);
        }
    }
    //Display output
    T.printTable();
}