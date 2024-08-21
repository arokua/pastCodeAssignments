#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
struct node{
    int nodeVal;
    struct node *left;
    struct node *right;
    int H;
};
struct node *rootN= NULL;
class AVLTree{
    
    public:
    
    //get tree height
    int height(struct node *atHere){
        int h = 0;//Begins at 0
        if (atHere != NULL){
            //Starts recursive loops for left and right branches to get height
            int lh = height(atHere->left);
            int rh = height(atHere->right);
            int maxH = max(lh,rh);
            h = maxH + 1;
        }
        return h;
    }   
    
    int getBalFactor(struct node *temp){
        int lh = height(temp->left);
        int rh = height(temp->right);
        int re = lh - rh;
        return re;
    }
    
    // //Rotations ops\\ \\
    
    struct node *LLrots(struct node *boss){
        struct node *midleGuy;
        
        midleGuy = boss->left;
        boss->left = midleGuy->right;
        midleGuy->right = boss;
        return midleGuy;
    }
    
    struct node *RRrots(struct node *boss){
        struct node *midleGuy;
        midleGuy = boss->right;
        boss->right = midleGuy->left;
        midleGuy->left = boss;
        return midleGuy;
    }
    
    struct node *LRrots(struct node *boss){
        struct node *midleGuy;
        midleGuy = boss->left;
        boss->left = RRrots(midleGuy);
        
        return LLrots(boss);
    }
    
    struct node *RLrots(struct node *boss){
        struct node *midleGuy;
        midleGuy = boss->right;
        boss->right = LLrots(midleGuy);
        
        return RRrots(boss);
    }
    
    //balance AVL tree for each insert and delete ops
    struct node *balance(struct node *holder){
        int balanceFactor = getBalFactor(holder);
        if (balanceFactor > 1){
            if (getBalFactor(holder->left) > 0){
                holder = LLrots(holder);
            } else{
                holder = LRrots(holder);
            }
        }
        
        else if (balanceFactor < -1){
            if (getBalFactor(holder->right) > 0){
                holder = RRrots(holder);
            } else{
                holder = RLrots(holder);
            }
        }
        return holder;
    }
    
    //Insertion
    struct node *insert(struct node *root, int value){
        
        if (root == NULL){
            //make new node
            root = new node;
            root->nodeVal = value;
            //No value yet
            root->left = NULL;
            root->right = NULL;
            return root;
        }
        
        else if (value < root->nodeVal){
            //Smaller value to left, larger to right
            root->left = insert(root->left,value);
            //Remodify the AVLTree
            root = balance(root);
            
        }

        else if (value > root->nodeVal){
            root->right = insert(root->right,value);
            //Remodify the AVLTree
            root = balance(root);
            
        }else {
            return root;
        }
        
        return root;
    }
    
    //Delletion
    struct node *deleteN(struct node *root,int val){
        if (root == NULL){
            return root;
        }
        else if (val > root->nodeVal){
            root->right = deleteN(root->right,val);
            root = balance(root);
        }else if (val < root->nodeVal){
            root->left = deleteN(root->left,val);
            root = balance(root);
        }else {
            if (root->left == NULL){
                if (root->right != NULL){
                    *root = *(root->right);
                }else {
                    root = NULL;
                }
            }else if (root->right == NULL){
                if (root->left != NULL){
                    *root = *(root->left);
                }else {
                    root = NULL;
                }
            }
        }
    }
    // //Print\\ \\
    
    void preOrder(struct node *full){
        if (full != NULL){
            
            cout << full->nodeVal<< " ";
            
            preOrder(full->left);
            preOrder(full->right);
        }
    }
    
    void inOrder(struct node *full){
        if (full != NULL){
            inOrder(full->left);
            cout << full->nodeVal<< " ";
            preOrder(full->right);
        }
    }
    
    void postOrder(struct node *full){
        if (full != NULL){
            
            preOrder(full->left);
            preOrder(full->right);
            cout << full->nodeVal<< " ";
        }
    }
};

int main() {
    
    AVLTree A;
    
    
    string command;
    cout<<"";
    cin>>command;
    string instructions;
    int pType = 0;//print Type
    
    if( command.substr(command.length()-4, 4) == " POST"){
        instructions = substr(0, int(command.length()) - 5);
        pType = 2;
    }else if( command.substr(command.length()-4, 4) == " PRE"){
        instructions = substr(0, int(command.length()) - 4);
        pType = 1;
    }
    else if( command.substr(command.length()-4, 3) == " IN"){
        instructions = substr(0, int(command.length()) - 3);
        pType = 3;
    }
    
    //slice string to get the corresponding input which in turn yields outpput with AVL tree function
    
}