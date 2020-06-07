/*
 * Author: Megan Chu
 * Date: May 25, 2017
 * PA4 C++ 100 Kevin Bacon
 *
 */
 
#include <fstream>
#include <ostream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>
#include <cstdlib>
#include <climits>
#define INPUT 3


using namespace std;

/**
 * main method to execute class traversal based on prereqs
 * Parameters: argc, number of arguments
 *             argv, pointer to string arguments
 */
int main(int argc, char** argv)
{
  // store courses to print to file
  unordered_map<string, string> courses;
  vector<string> all;
  vector<string> starters;

  if(argc != INPUT)
  {
    cout << "Invalid input" << endl;
    return -1;
  }

  ifstream infile(argv[1]); // read input
  while(infile)
  {
    string s;
    // get the next line
    if(!getline(infile, s)) break;
    istringstream ss(s);
    vector<string> record;
    while(ss)
    {
      string next;
      // get next course name
      if(!getline(ss, next, '\t')) break;
      record.push_back(next);
    }
    if(record.size() == 1) // starter course
    {
      starters.push_back(record[0]);
    }
    else if(record.size() == 2) // prereq course
    {
      courses.insert(make_pair(record[0], record[1]));
    }
  }
  infile.close();

  queue<string> explore;
  for(string e: starters) // use queue to order
  {
    explore.push(e); // push all starters onto queue
  }
  ofstream out;
  out.open(argv[2], ios::out | ios::trunc);
  while(!explore.empty())
  {
    string temp = explore.front(); // print to file all popped items
    out << temp << endl;
    starters.push_back(temp);
    explore.pop();
    if(courses.find(temp) == courses.end())
    {
      continue;
    }
    string next = (courses.find(temp))->second;
    courses.erase(temp);
    bool push = true;
    for(string s: starters)
    {
      if(s == next)
      {
        push = false;
      }
    }
    if(push)
    {
      explore.push(next);
    }
  }
  out.close();

}

