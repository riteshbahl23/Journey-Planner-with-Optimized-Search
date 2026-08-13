#ifndef PLANNER_H
#define PLANNER_H

// struct Station is defined in the dictionary.h

struct Journey {
  // define suitable fields here
  Dictionary list;
  Journey() {}
  void selecter( char st_1_name[],float st,char st_2_name[]);
  Entry* checkway(char st_2_name[],Entry e);
};

struct Query{
  // define suitable fields here
  Journey plan;
  void add(Station st_1,Station st_2);
  void listout(char name[],float st);
  void select( char st_1_name[],float st,char st_2_name[]);
};

class Planner {
  // define suitable fields here
  Query manager;
  public:
    void planner_start();
};

#endif
