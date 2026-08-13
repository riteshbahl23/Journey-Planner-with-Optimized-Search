#include"queue.h"
#include<iostream>
using namespace std;

// tail refers to  the index that is going to be filled 
template<class T> bool DynamicQueue<T>::isEmpty(){
    return (head==tail);// if head ==  tail then queue is empty
}

template<class T> bool DynamicQueue<T>::isFull(){
    return ( tail == (unsigned int) -1 ) ; // this is done to denote if the array has reached the max capacity.
    // considering the underflow since the tail is also unsigned int
}

template<class T> void DynamicQueue<T>::grow(){
    if (!isFull()) return;// double check
    unsigned int newsize = nextSize();// nextSize of the array
    T* B= new T[newsize];
    for (int i=head;i < head + N;i++) B[i-head] = A[i%N];
    // coping the array of N elements from head to head-1 in a circular fashion.
    delete[] A;// deleting the previous the 
    A = B;// coping the ptr
    head = 0;// changing the value of head.
    tail = N;// changing the value of tail. 
    N = newsize;// changing the size of the array
}

template<class T> unsigned int DynamicQueue<T>::size(){
    return (N-head+tail)%N;// N has been added inorder to prevent the negative numbers .
}

template<class T> void DynamicQueue<T>::QInsert(T x){   
    if (isFull()) grow();// growing the array when the no of the elements is N.
    A[tail]=x; // now insert the value into queue.
    if (size()==N-1 ) { // note that this is the size of the array before addition
        tail = -1; // since now the array would have N elements , the head must be equal to tail.
    }    // this small change to denote that  size has reached the max capacity.
    else tail=(tail+1)%N; // this is in other cases.
}

template<class T> bool DynamicQueue<T>::QDelete(T* x){
    if( isEmpty()) return false;
    x = &A[head];    // assigning the pointer
    head=(head+1)%N;// changing the value of head.
    return true;
}