#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// update the height of the nodes accordingly for insert and delete.
void BST::updateNodes(TreeNode* node){
  TreeNode* curr;
  curr = node;  
  while( curr!= nullptr){
    if (curr->left != nullptr && curr->right != nullptr ) 
      curr->height = (curr->right->height > curr->left->height) ? curr->right->height + 1 : curr->left->height + 1;
    else if (curr->left == nullptr && curr->right==nullptr)  curr->height = 1; // considering the height to be 1 for leaves.
    else if (curr->right == nullptr)  curr->height = curr->left->height + 1;
    else if (curr->left == nullptr) curr->height = curr->right->height + 1;
    curr = curr -> parent;
  }  
}
// deletes the node according to the usual method. 
void BST::deleteNode(TreeNode* node){
  TreeNode* parent = node->parent;
  if (node->left == nullptr && node->right == nullptr){ // no children case -> remove the node directly
    if (parent == nullptr) root =nullptr; // removing the root case
    else {
      if (parent->right==node) updateBSTParentChild(nullptr,parent,false);
      else updateBSTParentChild(nullptr,parent,true);
      node = nullptr;
    }
    updateNodes(parent);// updating the heights
  }
  else if (node->left==nullptr){ // only right child
    if (parent == nullptr) {
      root->right->parent = nullptr; // for the root case
      root = root->right;      
    }
    else{
      if (parent->right == node) updateBSTParentChild(node->right,parent,false);
      else updateBSTParentChild(node->right,parent,true);// otherwise
      node = nullptr;
    }
    updateNodes(parent);
  }
  else if (node->right==nullptr){// only left child case
    if (parent == nullptr) {
      root->left->parent = nullptr;
      root = root->left;// for the root case
    }
    else {
      if (parent->right == node) updateBSTParentChild(node->left,parent,false);
      else updateBSTParentChild(node->left,parent,true);// otherwise
      node = nullptr;
    }
    updateNodes(parent);
  }
  else{// two child case:- find the predecessor and copy into the node and delete the predeccesor.
    TreeNode* pre=node->left;
    while(pre->right!=nullptr) pre = pre ->right;
    *node = *pre;
    deleteNode(pre);
  }
}
// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST
bool BST::insert(int jrnyCode, int price)
{
  TreeNode* newnode = new TreeNode(jrnyCode,price);
  newnode->height = 1;
  TreeNode* child = root;
  TreeNode* parent = nullptr;
  while (child != nullptr ){ // traverse to the bottom of the tree that is point of addition of node
    if (BSTLessThan(child,newnode)) {
      parent = child; 
      child =child->right;
    }
    else if (BSTLessThan(newnode,child)){
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
      if (BSTLessThan(parent,newnode)) updateBSTParentChild(newnode,parent,false);
      else updateBSTParentChild(newnode,parent,true);
      updateNodes(parent);// updating the heights
    }
    return true;
  }
  return false;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  TreeNode *node = new TreeNode(jrnyCode,-1);
  TreeNode* child = root;
  TreeNode* parent = nullptr;
  while (child != nullptr){ // traverse till you find it 
    if (BSTLessThan(child,node)){
      parent =  child;
      child = child ->right;
    }
    else if (BSTLessThan(node,child)){
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

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode)
{
  TreeNode *node = new TreeNode(jrnyCode,-1);
  TreeNode* child = root;
  TreeNode* parent = nullptr;
  while (child != nullptr){
    if (BSTLessThan(child,node)){ // traverse according to the journey codes
      parent =  child;
      child = child ->right;
    }
    else if (BSTLessThan(node,child)){
      parent = child ;
      child = child ->left;
    }
    else { // traverse till you find the node.
      deleteNode(child);//delete the node then 
      return true;
    } 
  }
  return false;// if the node is not present.
}


