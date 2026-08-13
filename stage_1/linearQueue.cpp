#include"queue.h"

// tail refers to  the index that is going to be filled , not the index filled last.
template<class T> bool DynamicQueue<T>::isEmpty(){
    return (head==tail); // no element is there if head == tail
}

template<class T> bool DynamicQueue<T>::isFull(){
    return (size()==N);// full size of the array
}

template<class T> void DynamicQueue<T>::grow(){
    if (!isFull()) return;// double check
    T *B = new T[nextSize()];// another array
    // head = 0 and tail =  N . these conditions must satisfy as size() == N
    for (int i=head;i<tail;i++){
        B[i-head] = A[i];// copying the elements 
    } 
    N = nextSize();//changing the size of the array
    delete[] A;// deleting the previous array.
    A = B;// coping the ptr. 
    // changing the head and tail would be redudant.
}

template<class T> unsigned int DynamicQueue<T>::size(){
    return tail-head;// size of the queue
}

template<class T> void DynamicQueue<T>::QInsert(T x){
    if (tail == N && !isFull()){ // this is done to rearrange the array which 
        for (int i=0;i<size();i++) A[i] = A[i+head];// had reached the end of array before 
        tail = tail -head;//the size of the array has become N.
        head = 0;
    }
    else if (isFull()) grow();// if it is full then grow the array;
    A[tail] =x;// inserting the elements
    tail ++;// increasing the value of the tail
}

template<class T> bool DynamicQueue<T>::QDelete(T* x){
    if (isEmpty()) return false;// if empty , then grow the array;
    x = &A[head];// assigning head ptr to x
    head++;  // increasing the value of the head 
    return true;
}