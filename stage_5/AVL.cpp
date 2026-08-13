#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif
// to update the nodes in the AVL tree
void AVLTree::updateNodes(TreeNode* node){ 
  TreeNode* curr = node; 
  while( curr!= nullptr){ // start from the newnode parent to root.
    if (curr->left != nullptr && curr->right != nullptr ) // two child case
      curr->height = (curr->right->height > curr->left->height) ? curr->right->height + 1 : curr->left->height + 1;
    else if (curr->left == nullptr && curr->right==nullptr)  curr->height = 1; // leaf will have the height = 1
    else if (curr->right == nullptr)  curr->height = curr->left->height + 1; // only left child case
    else if (curr->left == nullptr) curr->height = curr->right->height + 1; // only right child case
    curr = curr -> parent;// move to its parent
  }  
}
// check imbalance in the tree 
bool AVLTree::checkImbalance(TreeNode* node){
  if (node == nullptr) return false; // not checking for nullptrs 
  int l= (node->left!=nullptr) ? node->left->height: 0 ; // checking the height of the left subtree
  int r= (node->right!=nullptr) ? node->right->height: 0; // checking the height of the right subtree
  return ( (l-r <=1) && (l-r >= -1) ); // comapre
}

bool AVLTree::deleteNode(TreeNode* Node){ // AVL Deletion
  if (Node->left==nullptr && Node->right==nullptr){ // case when the leaf is deleted 
    if (Node->parent == nullptr) root=nullptr; // root case when the root itself is deleted
    else {
      TreeNode* parent = Node->parent; // it's parent
      if (parent->right==Node) {
        updateAVLParentChild(nullptr,parent,false);// update the right child to be nullptr
      }
      else{
        updateAVLParentChild(nullptr,parent,true);// update the left child to be nullptr
      }
      Node= nullptr; // changing the node to be nullptr
      TreeNode* cnode; // child node
      TreeNode* gcnode; // grand child node
      TreeNode* node = parent; // the parent node 
      updateNodes(parent);// intial update of the nodes' height
      // rotation has to be done till the root to avoid imbalances
      while(node!= nullptr) { 
        if (!checkImbalance(node)){ // check for imbalance
          if (node == nullptr ) {return true;} // if it is out of the tree return true;
          else { 
            // choosing the cnode as child of node with higher height and gcnode as child of cnode with higher height 
            if (node->left != nullptr && node->right != nullptr) cnode = (node->left->height > node->right->height) ? node->left : node->right;
            else if (node->left == nullptr) cnode = node->right;
            else if (node->right == nullptr) cnode = node ->left;// node and gcnode are assured to have children
            if (cnode->left!=nullptr && cnode->right!=nullptr) gcnode = (cnode->left->height > cnode->right->height) ? cnode->left : cnode->right;
            else if (cnode->left==nullptr)gcnode= cnode->right;
            else if (cnode->right==nullptr)gcnode= cnode->left;
            // choosing the rotation accordingly.
            if (node->left == cnode && node->left->left == gcnode) {
              rotateLeftLeft(gcnode,cnode,node);        
            }
            else if (node->right == cnode && node->right->right==gcnode) {
              rotateRightRight(gcnode,cnode,node);        
            }
            else if (node->left==cnode && node ->left ->right==gcnode) {
              rotateLeftRight(gcnode,cnode,node);        
            }
            else if (node->right==cnode && node ->right->left== gcnode ) {
              rotateRightLeft(gcnode,cnode,node);
            }
          }
          updateNodes(cnode);// updating the heights
          updateNodes(gcnode);// updating the heights
          updateNodes(node);// updating the heights
        }
        node=node->parent;// moving up
      }
      
    }
    return true;
  }
  else if (Node->left == nullptr){ // only right child case
    *Node = *(Node->right);// copy its child and
    return deleteNode(Node->right);// delete the child
  }
  else if (Node->right == nullptr){// only left child case
    *Node = *(Node ->left);// copy its child and
    return deleteNode(Node->left);// delete its child
  }
  else {// two child case
    TreeNode *child = Node->left;
    while(child->right !=  nullptr){ // finding its predecessor and copying it 
      child=child->right;
    }
    *Node = *child;
    return deleteNode(child);// and delete the predecessor.
  }
  return false;
}

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // no changes made in this function except adding the special case when the greatGrandParentNode is nullptr
  //cout << "LL" << endl;
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  bool isGPLeftChild;
  if (greatGrandParentNode == nullptr ) { // grandparent is root.
    isGPLeftChild = true; // preventing the segfault.
    root = parentNode;// changing the root.
  }
  else if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  TreeNode *T3 = parentNode->right;

  // changing the pointers ..
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild); 
  updateAVLParentChild(currNode, parentNode, true);  
  updateAVLParentChild(grandParentNode, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // no changes made in this function except adding the special case when the greatGrandParentNode is nullptr
  //cout << "LR" << endl;
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  if (greatGrandParentNode == nullptr){ // grandparent is root
    isGPLeftChild = true; // default value
    root =  currNode ; // changing the root
  }
  else if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  // changing the pointers ..
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // similar to rotateLeftLeft()
  //cout << "RR" << endl;  
  TreeNode* greatGrandParent = grandParent->parent;
  bool isGPLeftChild;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  if (greatGrandParent == nullptr ) { // grandparent is root.
    isGPLeftChild = true; // preventing the segfault.
    root = parent;
  }
  else if (greatGrandParent->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParent->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }
  TreeNode* T3 = parent ->left;
  // changing the pointers ..
  updateAVLParentChild(parent,greatGrandParent,isGPLeftChild);
  updateAVLParentChild(currNode, parent,false);
  updateAVLParentChild(grandParent,parent,true);  
  updateAVLParentChild(T3,grandParent,false);
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // similar to rotateRightLeft()
  //cout << "RL" << endl;
  TreeNode* greatGrandParent = grandParent->parent;
  bool isGPLeftChild;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  if (greatGrandParent == nullptr ) { // grandparent is root.
    isGPLeftChild = true; // preventing the segfault.
    root = currNode;
  }
  else if (greatGrandParent->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParent->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }
  TreeNode* T2 = currNode->left;
  TreeNode* T3 = currNode->right;
  // changing the pointers ..
  updateAVLParentChild(currNode, greatGrandParent, isGPLeftChild);
  updateAVLParentChild(parent,currNode,false);
  updateAVLParentChild(grandParent,currNode,true);  
  updateAVLParentChild(T2,grandParent,false);
  updateAVLParentChild(T3,parent,true);
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  TreeNode* newnode = new TreeNode(jrnyCode,price);// newnode
  newnode->height = 1;// changing the height of the node to be 1
  TreeNode* child = root;// traverse till you find a suitable place
  TreeNode* parent = nullptr;
  while (child != nullptr ){ // traverse to the bottom of the tree that is point of addition of node
    if (AVLLessThan(child,newnode)) { // compare
      parent = child ; 
      child =child->right;
    }
    else if (AVLLessThan(newnode,child)){// compare the nodes
      parent = child;
      child = child ->left;
    }
    else {
      return false; // check of equality.
    }
  }
  if (child == nullptr){
    if (parent==nullptr) root = newnode; // root case
    else{
      if (AVLLessThan(parent,newnode)) updateAVLParentChild(newnode,parent,false);// adding the new node
      else updateAVLParentChild(newnode,parent,true);
      // rotation at the first point of imbalance 
      TreeNode* node=parent;  
      TreeNode* cnode= (node->left!=nullptr) ? node->left : node->right;// child node
      TreeNode* gcnode=(cnode->left!=nullptr) ? cnode->left : cnode->right;   // grandchild node  
      updateNodes(parent);// updating the heights
      while(checkImbalance(node)) { // finding the node
        gcnode = cnode;// in this case gcnode and cnode have to be in the path to the new node from root. 
        cnode = node;
        node=node->parent;
      }      
      // finding suitable rotation
      if (node == nullptr ) {return true;}
      else if (node->left == cnode && node->left->left == gcnode) {
        rotateLeftLeft(gcnode,cnode,node);        
      }
      else if (node->right == cnode && node->right->right==gcnode) {
        rotateRightRight(gcnode,cnode,node);        
      }
      else if (node->left==cnode && node ->left ->right==gcnode) {
        rotateLeftRight(gcnode,cnode,node);        
      }
      else if (node->right==cnode && node ->right->left== gcnode ) {
        rotateRightLeft(gcnode,cnode,node);
      }
      updateNodes(cnode);// updating the heights
      updateNodes(gcnode);// updating the heights
      updateNodes(node);// updating the heights
    }
    return true;
  }
  return false;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  TreeNode *node = new TreeNode(jrnyCode,-1);// dummy node used to compare
  TreeNode* child = root;
  TreeNode* parent = nullptr;
  while (child != nullptr){ // traverse till you find it 
    if (AVLLessThan(child,node)){
      parent =  child;
      child = child ->right;
    }
    else if (AVLLessThan(node,child)){
      parent = child ;
      child = child ->left;
    }
    else {
      return child->getPrice(); // incase both of if and else if fail ,then only possibility is equality.
    }
  }
  return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::remove(int jrnyCode)
{
  // tranversing the entire tree with a dummy node 
  TreeNode *node = new TreeNode(jrnyCode,-1);
  TreeNode* child = root;
  TreeNode* parent = nullptr;
  while (child != nullptr){
    if (AVLLessThan(child,node)){ // traverse according to the journey codes
      parent =  child;
      child = child ->right;
    }
    else if (AVLLessThan(node,child)){
      parent = child ;
      child = child ->left;
    }
    else { // traverse till you find the node.
      deleteNode(child);//then delete the node 
      return true;
    } 
  }
  return false;// if the node is not present.
}


