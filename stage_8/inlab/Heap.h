#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class TreeNode {
 public:
  T object;
  TreeNode<T> *left;
  TreeNode<T> *right;
  TreeNode<T> *parent;

  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = nullptr;
  }
  ~TreeNode() {;}
};

template <typename T> class Heap {
  TreeNode<T> *root;

  TreeNode<T> *findLastNode(TreeNode<T> *node);
  int findlevel(TreeNode<T> *node);
  void printHeap(TreeNode<T> *node );
 public:
  Heap() {root = nullptr;}
  ~Heap() {;}

  void insert(T obj);
  T delMax();
  T getMax() {
    if (root!=nullptr) return root->object;
  }
  void print();
  //  void displayAboveThresh(int thresh);
};
#endif

