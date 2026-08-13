#include "dictionary.h"
#include "planner.h"
#include "dictionary.cpp"
#include <string.h>
#include <iostream>
#include <fstream>

// this code automically does the input from the files and 
// writes the output into another file.

ifstream infile;
ofstream ofile;

Station::Station( char key[],float t){
    strcpy(name,key);
    time = t;
}

void Journey::selecter( char st_1_name[],float st,char st_2_name[]){
    int n;
    Entry* a= list.get(st_1_name,st,n);
    if (n==0) {
        ofile <<"ERROR\n";
        return;
    }
    for (int i=0;i<n;i++){
        int j=i;
        while ((a[j].st_1.time > a[j+1].st_1.time) && (j<n-1)){
            Entry e=a[j];
            a[j] = a[j+1];
            a[j+1] = e;
            j++;
        } 
    }
    for (int i=0;i<n;i++){
        if (strcmp(a[i].st_2.name,st_2_name) == 0){
            ofile <<a[i].st_1.time<<endl;
            return;
        }
        Entry* e = checkway(st_2_name,a[i]);
        if (e != NULL){
            ofile <<a[i].st_1.time<<" "<<a[i].st_2.name<<" "<<e->st_1.time<<endl;
            return;
        }
    } 
    ofile <<"ERROR\n";
    return;
}

Entry* Journey::checkway(char st_2_name[],Entry e){// this is function has to return the train that goes to st_2_name.
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

void Query::add(Station st_1,Station st_2){
    Entry e;
    e.set(st_1,st_2);
    /*cout << "add function :\n"
    << st_1.name <<" "<<st_2.name ;*/ 
    plan.list.put(e);
}
void Query::listout(char name[],float st){
    //plan.list.Printout();
    int n;
    Entry* a = plan.list.get(name,st,n);
    if (n==0) {
        ofile << "ERROR\n";
    }
    //cout <<"the value of n is:"<< n << endl;
    for (int i=0;i<n;i++){
        ofile << a[i].st_1.time << " " << a[i].st_2.name <<endl;
    }
    return;
}
void Query::select( char st_1_name[],float st,char st_2_name[]){
    plan.selecter(st_1_name,st,st_2_name);     
}

void Planner::planner_start(){
    char cmd[32];    
    while (true){
        ios_base::sync_with_stdio(false); cin.tie(0);
        //cout<< ">>> ";
        infile >> cmd;
        if (infile.eof()) return;
        if (strcmp(cmd,"EXIT") == 0) return;
        if (strcmp(cmd,"ADD") == 0){
            char st_1_name[32];
            float st;
            char st_2_name[32];
            float et;
            infile >> st_1_name >> st >> st_2_name >> et;
            Station st_1(st_1_name,st);
            Station st_2(st_2_name,et);
            manager.add(st_1,st_2);
            
        }
        if (strcmp(cmd,"QUERY_STATION") == 0){
            char st_1_name[32];
            float st;
            infile>>st_1_name >>st;
            manager.listout(st_1_name,st);
        }
        if (strcmp(cmd,"QUERY_JOURNEY") == 0){
            char st_1_name[32];
            float st;
            char st_2_name[32];
            infile >> st_1_name >> st >> st_2_name;
            manager.select(st_1_name, st ,st_2_name);
        }
    }
}

int main(int argc ,char* argv[]){
    // TODO
    infile.open(argv[1]);
    ofile.open(argv[2]);
    Planner p;
    p.planner_start();
}
