#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
int Heap<T>::findlevel(TreeNode<T> *node){
  int level = 0;
  while (node!= nullptr) {
    node=node->parent;
    level++;
  }
  return level;
}

template<typename T>
TreeNode<T> *Heap<T>::findLastNode(TreeNode<T> *currNode){
  if (currNode == nullptr)
  if (currNode->left == nullptr && currNode ->right == nullptr){
    return currNode;
  }
  else if (currNode->left != nullptr && currNode->right != nullptr) {
    TreeNode<T>*leftnode = findLastNode(currNode->left);
    TreeNode<T>*rightnode = findLastNode(currNode->right);
    if (findlevel(leftnode) < findlevel(rightnode)){
      return leftnode;
    }
    else if (findlevel(leftnode) > findlevel(rightnode)){
      return rightnode;
    }
    else {
      return leftnode;
    }
  }
  else if (currNode-> left != nullptr){
    return findLastNode(currNode->left);
  }
  return nullptr;
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *newNode = new TreeNode<T>(obj);
  if (root ==nullptr) {
    root = newNode;
    return;
  }
  TreeNode<T> *lastNodeParent = findLastNode(root);
  if (lastNodeParent ->left == nullptr) lastNodeParent->left = newNode;
  else if (lastNodeParent->left != nullptr) lastNodeParent->right = newNode;
  newNode->parent = lastNodeParent;
  return;
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here
  TreeNode<T> *currNode = root;
  while (true){
    if (currNode->left== nullptr && currNode->right==nullptr) {
      return currNode->object;
    }
    else if (currNode->left != nullptr && currNode->right==nullptr) {
      currNode->object = currNode->left->object;
      currNode = currNode->left;
    }
    else if (currNode ->right->object > currNode->left->object) {
      currNode->object = currNode->right->object;
      currNode = currNode->right;
    }
    else {
      currNode->object = currNode->left->object;
      currNode = currNode->left;
    }
  }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T>* node) {
  if (node == nullptr) return;
  // insert your code here
  cout << node->object << endl;
  cout << " |-";
  printHeap(node->left);
  cout << " |-";
  printHeap(node->right);
  return;
}

template<typename T>
void Heap<T>::print(){
  printHeap(root);
}

  
