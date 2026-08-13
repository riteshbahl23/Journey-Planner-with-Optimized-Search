Roll No: 210050059
Name : Gowtham S

Inlab_2 folder:
	This folder contains all the files that i have worked with in the inlab time for lab_2 .
	This includes dictionary.h where the declaration of the member functions is given, dictionary.cpp where all the member functions have been defined ,dictionaryTest.cpp where the interactive and
	automatic modules are defined,and the python files for the automatic testing of the dictionary.cpp.This automatic testing process have two outputs that is sample.txt where sample words were
	created by the python file,results.txt which is the output from the dictionaryTest.cpp for the automatic process and hash.png which contains the bar graph for the result obtained in results.txt.

	The functions are explained here :
	struct Entry has three data types that is key(char[32]) ,value (int) and TOMB_STONE (bool) , one member function setKeyAndValue and redefined default constructor.
	struct Entry has a default constructor which makes the first character of key to be '\0' which acts to be an indicator to be empty space.and sets the tombstone to be false.
	the function setKeyAndValue sets the value of the entry to given value and key of the entry to given key.
	
	In Class Dictionary, 
	redefined constructor makes a array on the heap and makes the size of the array to be stored in variable N.
	The function hashValue produces the hash value of a char array using the polynomial hash function as hash code map and for compression map,
	this function uses fibonacci hashing method using the inverse of golden ratio as A .
	The function findFreeIndex finds the free index for the given char array using the hashValue function and linear probing method.
	get function returns the pointer to the first entry in the dictionary which has the given key if not it returns NULL.
	put function puts the entry into the dictionary using the findFreeIndex function and sets the entry in the dictionary to that key and value .
	remove function removes the first entry with the given key from dictionary and returns true if deleted else returns false if such a entry can't be found.
	
	
Outlab_2 folder: 
	This folder contains planner.cpp,planner.h,dictionary.h,dictionary.cpp and other file planner_auto.cpp.
	
	The implementation of the Entry has been changed by adding elements of the struct station into it and also adding a assignment operator.
	The struct station has been defined here inorder to 
	avoid linkage problems.The implementation of the member function of dictionary class (get remove and put ), the default constructor of the Entry 
	and set function of Entry has been modified for the different Entry.
	The implementation of the dictionary class has been enhanced by overloading the function get to get an array of Entry elements which have the same key 
	and an float parameter is also used in order to find stations after the given time.
	
	The planner.h has the structs Journey ,query and the class Planner defined. the member function of the these classes and structs have been defined
	in the planner.cpp.Class planner has one data member that is Query manager this class has one function planner_start, this function starts the interactive
	terminal like environment in which you could use the 4 commands given.
	
	The struct Query has one data member that is the Journey plan. It has three member functions each for add a train details(add), listing the train detail
	(listout),listing the soonest journey details(select).the last function to find the soonest journey is implemented to call the member function 
	of Journey struct.The struct Journey has one data member that is Dictionary list.It has two member functions those are selector function that is used to
	select the soonest journey and checkway function to find if there is a way to another station.
	
	The file planner.cpp has the entire implementation of the functions declared in planner.h and also the interactive environment.
	The file planner_auto.cpp has the entire implementaion and it takes input file and output file as command line arguments.The input file must have all
	the queries .Output file gets created and it would all the responses to the queries.
	way to run it:
		g++ planner_auto.cpp
		./a.out  <input_file_name> <output_file_name>
 	

