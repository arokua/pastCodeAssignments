#include <iostream>
#include <string>
#include <vector>
#include <algorithm>// For the max function

using namespace std;

static int nodes[100];

//A leaf of a tree
class Node{
public:
    int data = 0;
    Node * left;
    Node * right;
    //Height of the tree
    int height = 0;
    Node(int dat){
        //Original parameers of each new node/leaf
        this->data = dat;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

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

int myHeights(Node *  me){
    //Return the height of a node, which is the maximum number of layers with that node as root
    if (me == NULL || me == nullptr) return 0;
    return me->height;
}

int updateHeights(Node* toUp){
    //Update the height of the given node
    return 1 + max(myHeights(toUp->left), myHeights(toUp->right));
}

int myData(Node * me){
    //Return the data of the given node, if it exist, other wise return -1
    if (me == NULL || me == nullptr) return -1;
    return me->data;
}

int heightDiff(Node * node){
	//Return the height difference between the left subtree and the right subtree of a node
	//Use for check balance
	return myHeights(node->left) - myHeights(node->right);
}
//The rotations components
    //Left rotation:Move current root to the left subtree
Node * L1(Node * oldRoot){
    //Temporary pointers to store existing data for later exchange
    Node * my_right = oldRoot->right;
    Node * leftOfRight = my_right->left;

    //Start switching data
    my_right->left = oldRoot;
    //the value of old left node of the new root is still larger than the value of old root
    oldRoot->right = leftOfRight;

    //Readjust tree heights accordingly
    oldRoot->height = updateHeights(oldRoot);
    my_right->height = updateHeights(my_right);    

    //Return the new root
    return my_right;
}

    //Right rotation:move current root to the right subtree
Node * R1(Node * oldRoot){
    //Temporary pointers to store existing data for later exchange
    Node * my_left;
    if (oldRoot->left != NULL)  my_left = oldRoot->left;
    else my_left = nullptr;
    Node * rightOfLeft = my_left->right;
    //Start switching data
    my_left->right = oldRoot;
    //the value of old left node of the new root is still smaller than the value of old root
    oldRoot->left = rightOfLeft;
    //Readjust tree heights accordingly
    oldRoot->height = updateHeights(oldRoot);
    my_left->height = updateHeights(my_left);

    //Return the new root
    return my_left;
}

//Insertion and rebalance when inserting function
Node * insert(Node* parent, int data){
    //Current node is empty
    if (parent == NULL){
        return new Node(data);
    }
    //Specifically for this program, no two nodes contains same data in the tree
    if (data > myData(parent)) parent->right = insert(parent->right, data);// go down to right subtree
    else if (data < myData(parent)) parent->left = insert(parent->left, data); // go to left subtree
    else return parent;
    //Increase the hegiht level of the parent node
    parent->height = updateHeights(parent);
    //check if the current tree is balanced
    // If the height different between the two subtrees is larger than 1 then it is unbalanced
    int balance_factor;
    balance_factor = heightDiff(parent);
    //Rebalancing
    if (balance_factor > 1){
        if (data < myData(parent->left)) return R1(parent); //Right
        else if (data > myData(parent->left)) {
            parent->left = L1(parent->left);
            return R1(parent); //Left right
        }
    }

    else if (balance_factor < - 1){
        if (data > myData(parent->right)) return L1(parent); //Left
        else if (data < myData(parent->right)) {
            parent->right = R1(parent->right);
            return L1(parent); //Right left
        }
    }
    //Node is still balanced
    return parent;
}

Node * maxValOfThisSub(Node * start){
    //Function to return the maximum in the subtrees of the given node
    Node * current = start;
    while (current->right != NULL){
        current = current->right;
    }
    return current;
}

Node * deleteNode(Node * now, int data){
    //Function to delete a node with given data from the tree and then rotate accordingly
    if (now == NULL){//Base case of nonexisting node, meaning the value is not in the tree
        return now;
    }
    //Choose to go to the left or right of the node first if the data does not match
    if (data > myData(now)) now->right = deleteNode(now->right, data);
    else if (data < myData(now)) now->left = deleteNode(now->left, data);
    //This is the node to be delete
    else {
        Node *temp;
        //No children case
        if (now->right == NULL && now->left == NULL){
            temp = now;
            now = NULL;
        }
        //Only one subtree either left or right
        else if (now->right == NULL) {
            temp = now->left; //Create a copy
            (*now) = (*temp); //pass it to the current node, as the ol data of that node have been deleted
            free(temp);
        }else if (now->left == NULL) {
            temp = now->right; //Create a copy
            (*now) = (*temp); //pass it to the current node, as the ol data of that node have been deleted
            free(temp);
        }
        else {
            temp = maxValOfThisSub(now->left); //Get the largest value of the left sub tree
            //Now change the node data
            now->data = temp->data;
            //Delete the swapped node
            now->left = deleteNode(now->left, temp->data);
        }
    }
    if (now == NULL) return NULL;
    //Now we check for the tree height and its balance-ness
    updateHeights(now);
    //Check balance
    int balance_factor = heightDiff(now);
    if (balance_factor > 1){
        if (heightDiff(now->left) >= 0 ) return R1(now);//Right
        else {
            now->left= L1(now->left);
            return R1(now); //left right
        }
    }
    else if (balance_factor < -1){
        if (heightDiff(now->right) <= 0 ) return L1(now); //Left
        else {
            now->right = R1(now->right);
            return L1(now); //Right left
        }
    }
    return now;
}
//Tree traversal
void preOrder(Node * start){
    //Order of traversal is root then left then right
    if (start != NULL) {
        cout << myData(start) << " ";
        //Check if left is empty
        //Then keeps running till the smallest node
        preOrder(start->left);
        //Then looks to the right to see if any node exist
        preOrder(start->right);
    }
}

void postOrder(Node * start) {
    //The order of this traversal is left then right then root
    if (start != NULL) {
        //Make sure not an empy node
        //Go to left subtree first
        postOrder(start->left);
        //Then go to the right to see if any node exist
        postOrder(start->right);
        //Finally print out the current node data
        cout << myData(start) <<" ";
    }
}

void inOrder(Node * start){
    if (start != NULL){
        inOrder(start->left);
        cout << start->data <<" ";
        inOrder(start->right);
    }
}
int main(){
    vector<string> commands = takeInput();
    string printOrder = commands.back();
    Node * root = NULL;
    //Read in all the delete and insert inputs
    for (int i = 0; i < int(commands.size()) - 1; i++){
        //The order given
        char cmd = commands[i].at(0);
        //The value that follows that order
        int number = stoi( commands[i].substr(1, int(commands[i].length()) - 1) );
        if (cmd == 'A') {
            if (nodes[number - 1] == 0){
                root = insert(root, number);
                nodes[number - 1] = 1;
            }
        }
        else {
            if (nodes[number - 1] ==1){
                root = deleteNode(root, number);
                nodes[number - 1] = 0;
            }
        }
    }
    size_t isZero = count(nodes, nodes + 100, 0);
    //Empty tree
    if (isZero == 100) cout <<"EMPTY";
    //Start splitting cases 
    else {
        if (printOrder == "IN"){
            inOrder(root);
        }else if (printOrder == "PRE") preOrder(root);
        else postOrder(root);
            cout <<endl;
        
    }
}   