#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
class DFS_class // a class to do DFS recursively
{

  StationAdjacencyList *adjacency; // adjacency array
  listOfObjects<TrainInfoPerStation *> **stationInfo; // stationInfo array
  Dictionary<int> stnNameToIndex; // dictionary
  int maxStopOvers; // max stopOvers
  int maxTransitTime; // max Transit time
  int index_of_src; // index of the source station
  int routes; // number of routes

public:
  DFS_class(StationAdjacencyList adjacency[512],listOfObjects<TrainInfoPerStation *> *(stationInfo)[512],Dictionary<int> stnNameToIndex,int maxStopOvers,int maxTransitTime)
  { // basic constructors
    this->adjacency =adjacency;
    this->stationInfo = stationInfo;
    this->stnNameToIndex =stnNameToIndex;
    this->maxStopOvers = maxStopOvers;
    this->maxTransitTime = maxTransitTime;
    routes = 0;
  }
  // ! NOTE note that jcs_so_far has the last node filled not the first node .same for stnIndexes 
  //  This is the recursive  function which carries the linked list of journey codes, linked list of station index, no of stops done.
  bool dfs(int index, int dest_index, int StopOvers, listOfObjects<int> *jcs_so_far, listOfObjects<int> *stnIndexes)
  {
    if (index == dest_index) // base case
    {
      print(jcs_so_far, stnIndexes);
      return true;
    }
    bool result = false; // bool inorder to check the result
    listOfObjects<StationConnectionInfo *> *tostation = adjacency[index].toStations; 
    if (tostation == nullptr) return false; // end station case checked
    listOfObjects<TrainInfoPerStation *> *train = tostation->object->trains; // accessing the trains list 
    // one call for each train making the program with a time complexity O(no of trains) + time taken to tranverse the linkedlist 
    while (tostation != nullptr)
    {
      int adj_index = tostation->object->adjacentStnIndex; // next station index      
      train = tostation->object->trains; // accessing the trains 
      while (train != nullptr)
      {
        listOfObjects<int> *newlist = new listOfObjects<int>(train->object->journeyCode); // making the new linked list
        newlist->prev = jcs_so_far; // add it to the linked list of the journey code
        int stops = StopOvers;
        if (jcs_so_far != nullptr) // check if there is a journey done before
        {
          if (jcs_so_far->object != newlist->object)// if they are not equal
          {
            stops++; // stop increased 
            listOfObjects<StationConnectionInfo *> *fromstation = adjacency[index].fromStations; 
            listOfObjects<TrainInfoPerStation *> *intrain = fromstation->object->trains;
            while(fromstation != nullptr) { // check for the previous train
              intrain = fromstation->object->trains;
              while (intrain != nullptr && intrain->object->journeyCode!=jcs_so_far->object) intrain = intrain->next;
              if (intrain != nullptr) break;
              fromstation =fromstation->next;              
            }
            if (stops > maxStopOvers || calculate(intrain,train) == -1) { // checking the constriants 
              train = train->next; // not satisifed
              continue; // next train
            }
          }          
          jcs_so_far->next = newlist; // connecting it completely
        }
        listOfObjects<int> *newstn = new listOfObjects<int>(adj_index); // adding the new station to the linked list
        newstn->prev = stnIndexes;
        if (stnIndexes != nullptr) stnIndexes->next = newstn;
        result = ( dfs(adj_index, dest_index, stops, newlist, newstn) || result); // recursive call
        train = train->next;
      }
      tostation = tostation->next; // next station
    }
    return result; // returning the boolean
  }

  void print(listOfObjects<int> *jcs_so_far, listOfObjects<int> *stnIndexes) // printing function 
  {
    routes ++;
    cout << "Route No:" << routes<< endl; // number of the routes 

    while (jcs_so_far->prev != nullptr){
      jcs_so_far = jcs_so_far->prev; // go to the intial node
    }
    while (stnIndexes->prev != nullptr){
      stnIndexes = stnIndexes->prev;// go to the intial node
    }
    listOfObjects<TrainInfoPerStation *> *trains,*prevtrains;
    while (stnIndexes->next != nullptr)
    {
      trains = stationInfo[stnIndexes->object];
      if (jcs_so_far->prev!=nullptr && jcs_so_far->prev->object != jcs_so_far->object){ // inorder to print the transit time
        while (trains != nullptr)
        {
          if (trains->object->journeyCode == jcs_so_far->object)
          {                   
            break;          
          }
          trains = trains->next; 
        }
        // printing the transit time 
        cout << "MIN. TRANSIT TIME:" << calculate(prevtrains,trains)/100<<" HOURS "<< calculate(prevtrains,trains)%100<<" MINS"<< endl;
        // change of train
        cout << "CHANGE TRAIN FROM JC:" << jcs_so_far->prev->object << " TO JC:"<< jcs_so_far->object << endl;
      }
      // from and to stations
      cout << stnNameToIndex.getKeyAtIndex(stnIndexes->object)<<" TO "<<stnNameToIndex.getKeyAtIndex(stnIndexes->next->object)<<endl;
      listOfObjects<StationConnectionInfo *> *tostation = adjacency[stnIndexes->next->object].fromStations;
      while (trains != nullptr)
      {
        if (trains->object->journeyCode == jcs_so_far->object)
        {                   
          printinfo(trains->object); // find the station and print
          //jcs_so_far = jcs_so_far->next;
          break;          
        }
        trains = trains->next; 
      }
      while (tostation!= nullptr){
        trains = tostation->object->trains;
        while (trains!=nullptr){
          if (trains->object->journeyCode == jcs_so_far->object){
            printinfo(trains->object);// this is the arrival and departure time at the next station
            prevtrains = trains; // storing the last train 
            jcs_so_far = jcs_so_far->next; // moving to the next journey code
            break;
          }
          trains=trains->next;
        }
        if (trains != nullptr){
          break;
        }
        tostation = tostation->next;
      }
      stnIndexes = stnIndexes->next;
    }
  }

  void printinfo(TrainInfoPerStation *currInfo) 
  {
    // a part of function as printStationInfo in the planner.h 
    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    if (currInfo != nullptr)
    {            
      cout << GREEN << "Day(s): " << RESET;
      for (int i = 0; i < 7; i++)
      {
        if (currInfo->daysOfWeek[i])
          cout << days[i] << " ";
      }
      cout << endl;
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      if (currInfo->arrTime == -1)
      {
        cout << "Starts";
      }
      else
      {
        cout << currInfo->arrTime;
      }
      cout << RED << " Dep: " << RESET;
      if (currInfo->depTime == -1)
      {
        cout << "Ends";
      }
      else
      {
        cout << currInfo->depTime;
      }
      cout << endl;
    }
  }

  int calculate(listOfObjects<TrainInfoPerStation *> *intrain,listOfObjects<TrainInfoPerStation *> *outtrain)
  {
    // calculates the transit time
    bool nextdayin = false,nextdayout=false;
    if (intrain->object->arrTime > intrain->object->depTime) nextdayin=true; // checking if the train leaves on the next day
    if (outtrain->object->arrTime > outtrain->object->depTime) nextdayout=true;
    int arr = intrain->object->arrTime;
    int dep = outtrain->object->depTime;
    int lastTime=-1;
    for (int i =0;i<7;i++){ // going through the array
        if (intrain->object->daysOfWeek[i] == outtrain->object->daysOfWeek[i] && outtrain->object->daysOfWeek[i] ){ // arrive on the same day
          if ( (!nextdayin && !nextdayout) || (nextdayin && !nextdayout)){ // second train departs on the same day
            if (dep-arr < 0 || (dep-arr)/100 > maxTransitTime ) continue;
            else return( (dep/100 - arr/100)*100 +( (dep%100 == 0 && arr%100 != 0) ? 60-(arr%100)-100 : (dep%100)-(arr%100) ) );
          }
          else if  ( (nextdayin && nextdayout) || (!nextdayin && nextdayout) ){ // second train departs on the next day
            if (((dep-arr)/100)+24 > maxTransitTime) continue;
            else return (dep/100 - arr/100)*100 +( (dep%100 == 0 && arr%100 != 0) ? 60-(arr%100)-100 : (dep%100)-(arr%100) )+2400;
          }
        }
        else if (intrain->object->daysOfWeek[i] < outtrain->object->daysOfWeek[i]) { // if the train arrives later than the second train
          if (nextdayout && intrain->object->daysOfWeek[i+1] && arr < dep){
            if ((dep-arr)/100 > maxTransitTime) continue;
            else return (dep/100 - arr/100)*100 +( (dep%100 == 0 && arr%100 != 0) ? 60-(arr%100)-100 : (dep%100)-(arr%100) );
          }
        }
        else if ((intrain->object->daysOfWeek[i] > outtrain->object->daysOfWeek[i])){ // if the train arrives before the second train arrives
          int j;for (j=i+1;j<7;j++) if (outtrain->object->daysOfWeek[j]) break;
          if (j<7){
            if (((dep-arr)/100)+24*(j-i) > maxTransitTime) continue;
            else {
              int lastTime1 = (dep/100 - arr/100)*100 +( (dep%100 == 0 && arr%100 != 0) ? 60-(arr%100)-100 : (dep%100)-(arr%100) )+2400*(j-i);
              if (lastTime == -1 || lastTime1 < lastTime) lastTime = lastTime1; // storing the last time and checking if it is less or not
            }
          }
        }
    }
    if (lastTime != -1) { 
      return lastTime; // last case
    }
    //return ((dep - arr >= 0) ? ((dep - arr)/100) : ((24 + dep - arr))/100);
    return -1; // returning false
  }  
};

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // source station index
  if (srcStnName == destStnName)
  {
    cout << "SAME SOURCE AND DESTINATION STATIONS" << endl;
    return;
  }
  int index = stnNameToIndex.hashValue(srcStnName);
  while (stnNameToIndex.getKeyAtIndex(index) != srcStnName)
    index = (index + 1) % DICT_SIZE;
  int dest_index = stnNameToIndex.hashValue(destStnName);
  while (stnNameToIndex.getKeyAtIndex(dest_index) != destStnName)
    dest_index = (dest_index + 1) % DICT_SIZE;
  //cout << dest_index << "to" << index << endl;
  DFS_class dfsclass(adjacency,stationInfo,stnNameToIndex,maxStopOvers,maxTransitTime); // make an object here copying takes linear time only for dictionary 
  listOfObjects<int> *node = new listOfObjects<int>(index);
  if (!dfsclass.dfs(index,dest_index,0,nullptr,node)){ // calling the function
    cout << stnNameToIndex.getKeyAtIndex(index)<<" TO "<<stnNameToIndex.getKeyAtIndex(dest_index)<<endl; // incase no way found
    cout << "NOT FOUND" << endl;
  }
  return;
}
#endif
