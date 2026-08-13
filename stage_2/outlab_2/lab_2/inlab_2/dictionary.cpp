#include "dictionary.h"
#include <cmath>
using namespace std;
Entry:: Entry() {
    for(int i=0;i<32;i++) key[i]='\0';
    TOMB_STONE=false;
}

void Entry:: setKeyAndValue( char Key[] , int value){
    strcpy(key,Key);
    this-> value = value;
    TOMB_STONE= false;
}

Dictionary::Dictionary() {
    A =  new Entry[DICT_SIZE];
    N = DICT_SIZE;
} 

int Dictionary::hashValue(char key[]){
    unsigned long long int value = key[0];// using unsigned long long to prevent the overflow.
    unsigned long long int  x = 33;// number suggested to reduce the number of the collisions 
    unsigned long long x_term =x;
    for(int i=1;key[i] != '\0';i++){
        value += ((key[i] * x_term )%(101111)) ;
        x_term *= x;
    }
    value = value%(101111);
    double fib = 0.618033989 ; // this is the inverse of golden ratio
    double hash_value = fib * value;
    double M = DICT_SIZE;
    hash_value = ( hash_value-floor(hash_value) );
    hash_value = M *hash_value;
    return ( floor(hash_value) );
}

int Dictionary::findFreeIndex(char key[]){
    int index = hashValue(key);
    if (A[index].key[0] == '\0') return index;// if the position at index is free then it returns index.
    for (int i=(index+1)%N ; i != index ; i=(i+1)%N ){// it iterates for N
        if (A[i].key[0] == '\0') return (i); // if empty position is found
    }
    return -1;// if no empty position is found then it returns -1.
}
  
struct Entry* Dictionary::get(char key[]){
    int index = hashValue(key);
    int i = index;
    while( !(A[i].key[0] == '\0') && !(A[i].TOMB_STONE) ){
        bool found = true;
        for (int j=0;key[j]!='\0';j++) if(A[i].key[j] != key[j]) found = false;
        if (found) return &A[i]; 
        i=(i+1)%N;
    }
    return NULL;
}

// Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
bool Dictionary::put(struct Entry e){
    int index=findFreeIndex(e.key);
    if (index==-1) return false;
    A[index].setKeyAndValue(e.key,e.value);
    return true;
}

// Remove the given key; return true if success, false if failure (given key not present)
bool Dictionary::remove(char key[]){
    int index= hashValue(key);
    int i=index;
    while( !(A[i].key[0] == '\0') ){
        bool found = true;
        for (int j=0;key[j]!='\0';j++) if(A[i].key[j] != key[j]) found = false;
        if (found) {
            // string found
            A[i].key[0]='\0';
            A[i].TOMB_STONE=true;
            return true;
        } 
        i=(i+1)%N;
    }
    return false;
}
