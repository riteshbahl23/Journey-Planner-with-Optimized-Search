#include <cmath>
using namespace std;


Entry:: Entry() {
    for(int i=0;i<32;i++) st_1.name[i]='\0'; // to signify empty space
    TOMB_STONE=false;
}

void Entry::set( Station st_1,Station st_2 ){
    strcpy(this->st_1.name,st_1.name);
    
    strcpy(this->st_2.name,st_2.name);
    
    this-> st_1.time = st_1.time;
    this-> st_2.time = st_2.time;// usual set function
    TOMB_STONE= false;
}
void Entry::operator=(Entry a){// assignment operator 
    strcpy(this->st_1.name,a.st_1.name);
    strcpy(this->st_2.name,a.st_2.name);
    this-> st_1.time = a.st_1.time;
    this-> st_2.time = a.st_2.time;
    TOMB_STONE=false;
}
Dictionary::Dictionary() {
    A =  new Entry[DICT_SIZE];
    N = DICT_SIZE;
} 

int Dictionary::hashValue(char key[]){// polynoimal hash functions
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
    double M = DICT_SIZE;// fibonacci compression hash map
    hash_value = ( hash_value-floor(hash_value) );
    hash_value = M *hash_value;
    return ( floor(hash_value) );
}

int Dictionary::findFreeIndex(char key[]){
    int index = hashValue(key);
    if (A[index].st_1.name[0] == '\0') return index;// if the position at index is free then it returns index.
    for (int i=(index+1)%N ; i != index ; i=(i+1)%N ){// it iterates for N
        if (A[i].st_1.name[0] == '\0') return (i); // if empty position is found
    }
    return -1;// if no empty position is found then it returns -1.
}
  
struct Entry* Dictionary::get(char key[]){// get function which returns only the first entry with the given key
    int index = hashValue(key);
    int i = index;
    while( !(A[i].st_1.name[0] == '\0') && !(A[i].TOMB_STONE) ){
        if (strcmp(A[i].st_1.name,key)==0) return &A[i]; 
        i = (i+1)%N;
    }
    return NULL;
}

struct Entry * Dictionary::get(char key[],float value,int &n){
    int index = hashValue(key);// this get function gives the array of the entry with the same key and whose value is greater than given value.
    int i = index;
    n=0;// this is a referenced variable it contains the size of the array inorder to reduce the time taken for computation
    Entry *e = new Entry[N];
    while( !(A[i].st_1.name[0] == '\0') && !(A[i].TOMB_STONE) ){
        if (strcmp(A[i].st_1.name,key)==0) {
            if (A[i].st_1.time >= value) {
                e[n].set(A[i].st_1,A[i].st_2);
                n++;
            } 
        }
        i = (i+1)%N;
    }
    return e;
}

// Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
bool Dictionary::put(struct Entry e){
    int index=findFreeIndex(e.st_1.name);
    if (index==-1) return false;
    A[index].set(e.st_1,e.st_2);
    return true;
}

// Remove the given key; return true if success, false if failure (given key not present)
bool Dictionary::remove(char key[]){
    int index= hashValue(key);
    int i=index;
    while( !(A[i].st_1.name[0] == '\0') ){
        if (strcmp(A[i].st_1.name,key)==0) {
            // string found
            A[i].st_1.name[0]='\0';
            A[i].TOMB_STONE=true;
            return true;
        } 
        i=(i+1)%N;
    }
    return false;
}

