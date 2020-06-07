/*
* Name: Megan Chu
* PID: A12814536
* Date: May 25, 2017
* CSE 100 PA3 C++ Kevin Bacon
*/

#include<iostream>
#include<ostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<set>
#include<cstdlib>
#include <ctime>
#include "Actor.h"
#include "Movie.h"
#include "ActorGraph.h"
#include "UnionFind.hpp"
#include "util.h"
#define INPUT 5
#define ACTORS 1
#define PAIRS 2
#define OUTPUT 3
#define UFIND 4
#define NANO 1000000

using namespace std;

/**
 * main method to execute Kevin Bacon year connected
 * Parameters: argc, number of arguments
 *             argv, pointer to string arguments
 */
int main(int argc, char** argv)
{
  Timer time;  
  bool unionFind = false;
  if(argc == (INPUT - 1)) 
  // need input and output files as arguments
  {
    unionFind = true;    
  }
  else if(argc != INPUT)
  {
    cout << "Invalid input" << endl;
    return -1;
  }
  else
  {
    string uFind(argv[UFIND]);
    if(uFind.compare("ufind") == 0)
    {
      unionFind = true;
    }
    else if(uFind.compare("bfs") == 0)
    {
      unionFind = false;
    }
    else
    {
      cout << "Invalid input: ufind or bfs?" << endl;
      return -1;
    }
  }
  
  if(unionFind)
  {
    UnionFind upTree;
    cout << "Reading " << argv[ACTORS] << " ..." << endl;
    upTree.loadFromFile(argv[ACTORS]); // load file to graph
    cout << "done" << endl;
    cout << "\n  Running Union Find\n" << endl;

    time.begin_timer();
    upTree.find(argv[ACTORS], argv[PAIRS], argv[OUTPUT]);
   
    cout << "The duration in milliseconds is : " 
         << (double)time.end_timer()/NANO << endl << endl;
  }
  else
  {
    ActorGraph web; // create graph
    cout << "Reading " << argv[ACTORS] << " ..." << endl;
    web.loadFromFile(argv[ACTORS], false); // load file to graph
    web.clearEdges();
    cout << "done" << endl;
    cout << "\n  Running BFS\n" << endl;

    time.begin_timer();
    web.actorConnections(argv[PAIRS], argv[OUTPUT]);
    
    cout << "The duration in milliseconds is : " 
         << (double)time.end_timer()/NANO << endl << endl;
  }
  return 0;
}
