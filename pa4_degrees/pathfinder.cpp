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
#include "Actor.h"
#include "Movie.h"
#include "ActorGraph.h"
#define INPUT 5
#define ACTORS 1
#define WEIGHT 2
#define PAIRS 3
#define OUTPUT 4

using namespace std;


/**
 * main method to execute Kevin Bacon shortest path finder
 * Parameters: argc, number of arguments
 *             argv, pointer to string arguments
 */
int main(int argc, char** argv)
{
  if(argc != INPUT) // need input and output files as arguments
  {
    cout << "Invalid input" << endl;
    return -1;
  }

  ActorGraph web; // create graph
  string weight = argv[WEIGHT];
  char c = weight[0];
  cout << "Reading " << argv[ACTORS] << " ..." << endl;
  web.loadFromFile(argv[ACTORS], c == 'w'); // load file to graph
  cout << "done" << endl;

  web.computePath(argv[PAIRS], argv[OUTPUT]); // find shortest path in graph

}
  

