Roll No:: 210050059
Name:: Gowtham S

linearQueue.cpp:
    In this file , the implementation of the functions in the class DynamicQueue is done in such a way to implement the Linear queue.
    that is the queue is such a way that the head is always less than tail except in the case when the queue is empty, the head will 
    be equal to tail.

    the function isEmpty() returns true if the head is equal to tail that is when the queue is empty else it returns false.

    the function size() returns the size of the queue that is value of tail-head.

    the function isFull() returns true if the size() is N that is equal to the size of the array.this occurs only in the case when 
    the head is 0 and the tail is N.

    the function grow() is used to grow the array size to the next size which is given by the nextSize() function in the queue.h 
    only when the size of the queue becomes N , it grows the array linearly that is there is some constant growth whenever the
    queue becomes full.I have copied the elements into the new array and delete the old array and renamed  the new array
    into A and changed the size of the array N and haven't changed the value of head and tail as the head must be at 0 and tail must
    be at N for the size of the array to be N. 

    the function QInsert(T x) is used to insert the element in the queue at the end , whenever the queue is full the grow() function 
    is called ,but this function grow() is called only when the (N+1)th element is inserted.But if the tail reaches the end of the 
    array before the size of queue becomes equal to size of the array, the array is rearranged in a way to move the head to zero 
    and the tail accordingly.this process makes the linear queue more time expensive and makes it certain that the size of the 
    queue can become equal to size of the array.at last the value of tail is incremented.

    the function QDelete(T* x) is used to delete the element in the queue at the head position. the function returns false if 
    the queue is empty and returns true if the queue is not empty. before returning , the pointer is assigned to the head  
    that is to be delete, and value of the head is changed.

circularQueue.cpp:
    In this file , the implementation of the function in the class DynamicQueue is done in such a way to implement the idea of the 
    queue  in a circular fashion that is tail would be equal to head in the start when the queue is empty and the tail tries to reach 
    the value of head in a circular fashion. This is possible by using the mod operator(%) that calculates the remainder of first number when 
    divided by the second number(like 5%3 = 2).

    the function  size() returns the size of the queue that is (N-head+tail)%N ,N is added inorder to avoid the negative size which can occur
    if the head is greater than tail .The problem with the expression for the size() is that if head is equal to tail , it evaluates to 0 
    in both cases that is when the queue is empty and also when the queue is full. So, inorder to remove this confusion I have set 
    the value of tail to be (unsigned int) -1 when the size of the queue becomes equal to the size of the array.I have used '(unsigned int) -1'
    inorder to use make the tail point to the max value of unsigned int ,considering the overflow due to the unsigned nature of tail.

    the function isEmpty() returns true if the tail is equal to head else it returns false.
    
    the function isFull() returns true if the tail is equal to '(unsigned int) -1' that is the max value of the unsigned int .

    the function grow() function grows the length of the array to the next size as specified by the nextSize() function. the array is grown linearly 
    when the size of the queue is equal to the size of the array.I have copied the elements into the new array and delete the old array 
    and renamed  the new array into A and changed the value of head to 0, tail to N(value before incrementing ), and size of the array N.

    the function QInsert( T x) inserts the element of the value x at the end of the queue. This function calls the grow() function when the 
    size of the queue is equal to size of the array that is exactly when the tail. this function makes the value of the tail to be (unsigned int) -1
    that is equal to the max value of the unsigned int when the size of queue is N-1 and the new element is being inserted.under other conditions , it 
    shall be incremented the value of tail and its remainder with respect to N (size of the array) would be the value of the tail.

    the function QDelete(T* x) deletes the head of the queue. the pointer x is referenced to head of the queue that is going to be 
    deleted. the head is also incremented and  its remainder with respect to N (size of the array) would be the value of the head. 
    this function returns true if the queue is non empty and returns false if the queue is empty.