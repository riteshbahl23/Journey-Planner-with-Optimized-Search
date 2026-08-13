#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
    root = nullptr;
}
BST::BST(TreeNode *root){ 
    this->root=root; 
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    // iterative procedure
    TreeNode *parent = nullptr;
    TreeNode *child = root;
    if (root == nullptr) {// intial case 
        root = new TreeNode(JourneyCode,price,nullptr,nullptr,nullptr);
        return true;
    }
    while ( (child != nullptr) && (child->JourneyCode != JourneyCode) ){// traverse till you find a leaf 
        if (child->price >= price){ // go to left node 
            parent = child;
            child = child->left;
        }
        else if (child->price < price){ // go to right node
            parent = child;
            child = child->right;
        }
    }
    if (child == nullptr){// insert only if the u had found a node.
        TreeNode *new_node = new TreeNode(JourneyCode,price,nullptr,nullptr,parent);
        if (parent->price >= price) parent->left = new_node;
        else parent->right = new_node;
        return true;
    }    
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    // recursion 
    if (root == nullptr) return false;
    if (root->price == price && root->JourneyCode == JourneyCode) return true;
    else if (root->price >= price) {// move to left node.
        BST leftSubTree(root->left);
        return leftSubTree.find(JourneyCode,price);
    }
    else if (root->price < price) {
        BST rightSubTree(root->right);// move to right node.
        return rightSubTree.find(JourneyCode,price);
    }
    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if (root == nullptr) return false;
    if ((root->JourneyCode==JourneyCode) && (root->price==price) ){// node found
        if ( root->left == nullptr && root->right == nullptr){// no child case
            if (root->parent ==  nullptr) {
                root=nullptr;
                return true;
            }
            TreeNode *parent = root-> parent;
            if( parent->price >= price ) parent->left = nullptr; 
            else parent->right = nullptr;
            root = nullptr;
            return true;            
        }
        else if ( root->left ==nullptr ){// only right child case
            if (root->parent ==nullptr){
                root=root->right;
                root->parent = nullptr;                
                return true;
            }
            TreeNode *parent = root->parent;
            if( parent->price >= price ) parent->left = root->right; 
            else parent->right = root->right;
            root->right->parent = parent;
            root =nullptr;
            return true;
        }   
        else if ( root->right ==nullptr ){// only left child case
            if (root->parent ==nullptr){
                root=root->left;
                root->parent = nullptr;                
                return true;
            }
            TreeNode *parent = root->parent;
            if( parent->price >= price ) parent->left = root->left; 
            else parent->right = root->left;
            root->left->parent = parent;
            root =nullptr;
            return true;
        }
        else {// two child case
            TreeNode *child = root->left;
            while (child->right != nullptr){
                child = child->right;
            }
            root->JourneyCode=child->JourneyCode;//coping the predecessor into root.
            root->price = child->price;
            BST leftSubTree(root->left);
            return leftSubTree.remove(root->JourneyCode,root->price);// removing the copy of predecessor
        }
    }
    else if (root->price >= price) {// recursion
        BST leftSubTree(root->left);
        return leftSubTree.remove(JourneyCode,price);
    }
    else if (root->price < price) {
        BST rightSubTree(root->right);
        return rightSubTree.remove(JourneyCode,price);
    }
    return false;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if (typeOfTraversal==  PRE_ORDER){// pre order traversal
        if (root == nullptr) return;// node before children
        cout << root->JourneyCode <<"\n";
        BST leftSubTree(root->left);
        leftSubTree.traverse(PRE_ORDER);
        BST rightSubTree(root->right);
        rightSubTree.traverse(PRE_ORDER);
    }
    else if (typeOfTraversal==  POST_ORDER){// post order traversal
        if (root == nullptr) return;// children before node
        BST leftSubTree(root->left);
        leftSubTree.traverse(POST_ORDER);
        BST rightSubTree(root->right);
        rightSubTree.traverse(POST_ORDER);
        cout << root->JourneyCode<<"\n";
    }
    else if (typeOfTraversal==  IN_ORDER){// in order tranversal
        if (root == nullptr) return;// left child then node then right child.
        BST leftSubTree(root->left);
        leftSubTree.traverse(IN_ORDER);
        cout << root->JourneyCode<<"\n";
        BST rightSubTree(root->right);
        rightSubTree.traverse(IN_ORDER);
    }  
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {// gets the minimum price of all the nodes in the tree
    TreeNode *child = root;
    while (child ->left != nullptr){
        child =child->left;
    }
    return child->price; 
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {return 0; }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { return; }
	
// While loading a tree from a file written by customStore, we
// can have one of two modes of loading.  We could either ask
// for the entire tree to be loaded or only the left subtree of
// the root (if it exists) to be loaded.  The loadMode flag
// takes one of two values LOAD_FULL_BST or LOAD_LEFT_SUBTREE,
// that are #defined in BST.cpp.
// If loadMode is LOAD_FULL_BST, customLoad should load the
// entire BST that was stored in filename using customStore.
// If loadMode is LOAD_LEFT_SUBTREE, customLoad should load
// only the left subtree of the root of the BST that was
// stored in filename using customStore.
// Your implementation of customLoad should be efficient --
// its time and space complexity should be linear in the size
// of the tree that is being loaded.  So, for example, if the
// left sub-tree of the root is small compared to the right
// sub-tree, customLoad's time and space complexity should
// be small even though the entire BST may be very large.
 
void BST::customLoad (int flag, string filename) { return; }


// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__" );

        // print the value of the node
        result.push_back(root->JourneyCode + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult(){
    result.clear();
}

vector<string> BST::getResult(){
    return result;
}