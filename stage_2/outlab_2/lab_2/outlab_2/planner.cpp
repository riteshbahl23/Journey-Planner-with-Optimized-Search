#include "dictionary.h"
#include "planner.h"
#include "dictionary.cpp"
#include <string.h>
#include <iostream>

Station::Station( char key[],float t){// constructor
    strcpy(name,key);
    time = t;
}

void Journey::selecter( char st_1_name[],float st,char st_2_name[]){ 
// it selects the journey if the first station name and starting time and the second station name is given
    int n;
    Entry* a= list.get(st_1_name,st,n);// gets the list of  trains from the first station after time t.
    if (n==0) {
        cout <<"ERROR\n";
    }
    for (int i=0;i<n;i++){// bubble sort is used since the max number of elements in the dictionary is limited to 64.
        int j=i;
        while ((a[j].st_1.time > a[j+1].st_1.time) && (j<n-1)){
            Entry e=a[j];
            a[j] = a[j+1];
            a[j+1] = e;
            j++;
        } 
    }
    for (int i=0;i<n;i++){// finding the soonest journey.
        if (strcmp(a[i].st_2.name,st_2_name) == 0){
            cout<<a[i].st_1.time<<endl;
            return;
        }
        Entry* e = checkway(st_2_name,a[i]);
        if (e != NULL){
            cout <<a[i].st_1.time<<" "<<a[i].st_2.name<<" "<<e->st_1.time<<endl;
            return;
        }
    } 
    cout <<"ERROR\n";
    return;
}

Entry* Journey::checkway(char st_2_name[],Entry e){// this function has to return the train that goes to st_2_name.
    int n;
    Entry* en = list.get(e.st_2.name,e.st_2.time,n);
    int index=-1;
    for (int i=0;i<n;i++){
        if (strcmp(en[i].st_2.name,st_2_name)==0){
            if (index==-1) index=i;
            if (en[i].st_1.time < en[index].st_1.time) index=i;
        }
    }
    if (index == -1) return NULL;
    else return &en[index];
}

void Query::add(Station st_1,Station st_2){ // for adding the station
    Entry e;
    e.set(st_1,st_2);
    /*cout << "add function :\n"
    << st_1.name <<" "<<st_2.name ;*/ 
    plan.list.put(e);
}
void Query::listout(char name[],float st){ // for listing out the trains 
    //plan.list.Printout();
    int n;
    Entry* a = plan.list.get(name,st,n);
    if (n==0) {
       cout<< "ERROR\n";
    }
    //cout <<"the value of n is:"<< n << endl;
    for (int i=0;i<n;i++){
        cout<< a[i].st_1.time << " " << a[i].st_2.name <<endl;
    }
    return;
}
void Query::select( char st_1_name[],float st,char st_2_name[]){
    plan.selecter(st_1_name,st,st_2_name);     // calls out the function in Journey struct
}

void Planner::planner_start(){// interactive environment.
    char cmd[32];    
    while (true){
        cout<< ">>> ";
        cin>> cmd;
        if (strcmp(cmd,"EXIT") == 0) return;
        if (strcmp(cmd,"ADD") == 0){
            char st_1_name[32];
            float st;
            char st_2_name[32];
            float et;
            cin>> st_1_name >> st >> st_2_name >> et;
            Station st_1(st_1_name,st);
            Station st_2(st_2_name,et);
            manager.add(st_1,st_2);
            
        }
        if (strcmp(cmd,"QUERY_STATION") == 0){
            char st_1_name[32];
            float st;
            cin>>st_1_name >>st;
            manager.listout(st_1_name,st);
        }
        if (strcmp(cmd,"QUERY_JOURNEY") == 0){
            char st_1_name[32];
            float st;
            char st_2_name[32];
            cin>> st_1_name >> st >> st_2_name;
            manager.select(st_1_name, st ,st_2_name);
        }
    }
}

int main(){
   
    Planner p;
    p.planner_start();
}
