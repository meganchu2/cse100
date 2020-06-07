/*
 * ActorGraph.cpp
 * Author: Megan Chu
 * Date: May 25, 2017
 *
 * This file is meant to exist as a container for starter code that you can 
 * use to read the input file format defined in movie_casts.tsv. Feel free 
 * to modify any/all aspects as you wish.
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
#include "ActorGraph.h"
#include "Actor.h"
#include "Movie.h"
#define YEAR 2015

using namespace std;

ActorGraph::ActorGraph(void) {} // default constructor


/** 
 * Load the graph from a tab-delimited file of actor->movie relationships.
 *
 * in_filename - input filename
 * use_weighted_edges - if true, compute edge weights as 
 * 1 + (2015 - movie_year), otherwise all edge weights will be 1
 *
 * return true if file was loaded sucessfully, false otherwise
 */
bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges)
{
  weighted = use_weighted_edges; // use weights when finding shortest path
  // Initialize the file stream
  ifstream infile(in_filename);

  bool have_header = false;

  // keep reading lines until the end of file is reached
  while (infile) 
  {
    string s;

    // get the next line
    if (!getline( infile, s )) break;
    if (!have_header) 
    {
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss) 
    {
      string next;
   
      // get next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;
      record.push_back( next );
    }

    if (record.size() != 3) 
    {
      // we should have exactly 3 columns
      continue;
    }

    string actor_name(record[0]);
    string movie_title(record[1]);
    int movie_year = stoi(record[2]);
    string movie_key = movie_title + record[2];

    // we have an actor/movie relationship, now what?
    actors.insert(make_pair(actor_name, new Actor(actor_name)));    
    // if new actor create new node
    Actor* newAct = (actors.find(actor_name))->second; // current actor

    movies.insert(make_pair(movie_key, 
                            new Movie(movie_title, movie_year)));
    Movie* movieLink = (movies.find(movie_key))->second; // current movie

    for(vector<Actor*>::iterator aItr = ((movieLink)->actors).begin(); 
        aItr != ((movieLink)->actors).end(); aItr++) // every actor in movie
    {
      (newAct->connections).push_back(make_pair(*aItr, movieLink));
      ((*aItr)->connections).push_back(make_pair(newAct, movieLink));
      edges += 2; // undirected edges
    }
    (movieLink->actors).push_back(newAct); 
    // add actor to list of actors in this movie
  }

  if (!infile.eof()) 
  {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();
  
  cout << "#nodes: " << actors.size() << endl;
  cout << "#movies: " << movies.size() << endl;
  cout << "#edges: " << edges << endl;

  return true;
}


/**
 *
 */
void ActorGraph::addEdges(int year)
{
  for(pair<string, Movie*> m : movies)
  {
    if((m.second)->year == year)
    {
      for(vector<Actor*>::iterator itr = ((m.second)->actors).begin(); 
          itr != ((m.second)->actors).end(); itr++)
      {
        if(itr + 1 == ((m.second)->actors).end())
        {
          break;
        }
        for(vector<Actor*>::iterator itr2 = itr + 1; 
            itr2 != ((m.second)->actors).end(); itr2++)
        {
          ((*itr)->connections).push_back(make_pair(*itr2, m.second));
          ((*itr2)->connections).push_back(make_pair(*itr, m.second));
          edges += 2;
        }
      }
    }
  }
}


/**
 * compute the paths between two actors given by a tab-delimited file of
 * actor->actor relationships to compute
 * Parameters: in_filename, input file of relationships to compute
 *             out_filename, output file to write path
 */
void ActorGraph::computePath(const char* in_filename, const char* out_filename)
{
  ofstream out;
  out.open(out_filename, ios::out | ios::trunc);
  out << "(actor)--[movie#@year]-->(actor)--..." << endl; // outfile header
  ifstream infile(in_filename);

  bool have_header = false;

  // keep reading lines until the end of file is reached
  while (infile) 
  {
    string s;

    // get the next line
    if (!getline( infile, s )) break;
    if (!have_header) 
    {
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss) 
    {
      string next;
   
      // get next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;
      record.push_back( next );
    }

    if (record.size() != 2) 
    {
      // we should have exactly 2 columns
      continue;
    }

    string actor1Name(record[0]);
    string actor2Name(record[1]);
    cout << "Computing path for (" << actor1Name << ") -> (" << actor2Name 
         << ")" << endl;
    Actor* actor1 = (actors.find(actor1Name))->second; // get start actor
    Actor* actor2 = (actors.find(actor2Name))->second; // get end actor

    queue<Actor*> explore; // actors to explore  
    vector<pair<int, Actor*>> exploreW; 
    if(weighted)
    {
      actor2->dist = 0;
      exploreW.push_back(make_pair(0, actor2)); 
      // explore from end so we can print reverse
      weightHelper(exploreW, actor1);
    }
    else
    {
      actor2->dist = 1;
      explore.push(actor2); // explore from end so we can print reverse
      pathHelper(explore, actor1); // find shortest path
    }

    out << "(" << actor1->name << flush;
    printHelper(out, actor1, actor2); // print path

    for(unordered_map<string, Actor*>::iterator itr = actors.begin(); 
        itr != actors.end(); itr++) // reset all searched nodes
    {
      (itr->second)->done = false;
      (itr->second)->prev = NULL;
      (itr->second)->dist = INT_MAX;
    }
  }

  if (!infile.eof()) 
  {
    cerr << "Failed to read " << in_filename << "!\n";
  }
  infile.close(); 
  out.close(); 
}


/**
 * helper method to recursively print shortest path
 * Parameters: out, output stream to write to
 *             curr, current actor info to print
 *             end, last actor infor to print
 */
void ActorGraph::printHelper(ofstream& out, Actor* curr, Actor* end)
{
  if(curr == end) // stop if we have printed last node
  {
    out <<")" << endl;
    return;
  }
  for(pair<Actor*, Movie*> a: curr->connections) 
  // print movie connection and next actor node
  {
    if(a.first == curr->prev)
    {
      out << ")--[" << a.second->title << "#@" << a.second->year << "]-->(" 
          << a.first->name << flush;
      printHelper(out, a.first, end);
      break;
    }
  }
}


/**
 *
 */
void ActorGraph::actorConnections(const char* in_filename, 
                                  const char* out_filename)
{
  int minYear = YEAR;
  for(pair<string, Movie*> m: movies)
  {
    if((m.second)->year < minYear)
    {
      minYear = (m.second)->year;
    }
  }
  ofstream out;
  out.open(out_filename, ios::out | ios::trunc);
  out << "Actor1\tActor2\tYear" << endl; // outfile header
  ifstream infile(in_filename);

  bool have_header = false;

  // keep reading lines until the end of file is reached
  while (infile) 
  {
    int recentYear = minYear;
    string s;

    // get the next line
    if (!getline( infile, s )) break;
    if (!have_header) 
    {
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss) 
    {
      string next;
   
      // get next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;
      record.push_back( next );
    }

    if (record.size() != 2) 
    {
      // we should have exactly 3 columns
      continue;
    }

    string actor1Name(record[0]);
    string actor2Name(record[1]);
    
    if(actors.find(actor1Name) == actors.end() || 
       actors.find(actor2Name) == actors.end())
    {
      out << actor1Name << "\t" << actor2Name << "\t" << "9999" << endl;
      return;
    }   

    Actor* actor1 = (actors.find(actor1Name))->second; // get start actor
    Actor* actor2 = (actors.find(actor2Name))->second; // get end actor

    addEdges(recentYear); // add edges for earliest year
    queue<Actor*> explore; // actors to explore  
    actor2->dist = 1;
    explore.push(actor2); // explore from end so we can print reverse

    while(!pathHelper(explore, actor1)) // no path
    {
      if(recentYear == YEAR)
      {
        out << actor1Name << "\t" << actor2Name << "\t" << "9999" << endl;
        return;
      }
      for(unordered_map<string, Actor*>::iterator itr = actors.begin(); 
          itr != actors.end(); itr++) // reset all searched nodes
      {
        (itr->second)->prev = NULL;
        (itr->second)->dist = INT_MAX;
      }
      recentYear++;
      addEdges(recentYear);
    } // after loop we have found path
    out << actor1Name << "\t" << actor2Name << "\t" << recentYear << endl;
    for(unordered_map<string, Actor*>::iterator itr = actors.begin(); 
        itr != actors.end(); itr++) // reset all searched nodes
    {
      (itr->second)->prev = NULL;
      (itr->second)->dist = INT_MAX;
    }
    clearEdges();
  }

  if (!infile.eof()) 
  {
    cerr << "Failed to read " << in_filename << "!\n";
  }
  infile.close(); 
  out.close(); 
}


/**
 *
 */
void ActorGraph::clearEdges()
{
  for(unordered_map<string, Actor*>::iterator itr = actors.begin(); 
      itr != actors.end(); itr++) // reset all searched nodes
  {
    ((itr->second)->connections).clear();
  }
  edges = 0;
}
  

/**
 * helper method to find shortest path using a queue
 * Parameters: explore, queue of actors to compare to target
 *             find, target actor to find
 */
bool ActorGraph::pathHelper(queue<Actor*> explore, Actor* find)
{
  while(explore.size() > 0) // explore if nodes in queue
  {
    Actor* curr = explore.front();
    explore.pop();
    if(curr == find) // if we found actor stop
    {
      return true;
    }
    for(pair<Actor*, Movie*> a: curr->connections) 
    // explore all connections of current actor
    {
      if(a.first->dist == INT_MAX)
      {
        (a.first)->prev = curr;
        explore.push(a.first);
        a.first->dist = 1;
      }
    }
  }
  return false;
}


/**
 * helper method to find shortest path using a queue for weighted graph
 * Parameters: explore, queue of actors to compare to target
 *             find, target actor to find
 */
void ActorGraph::weightHelper(vector<pair<int, Actor*>> explore, Actor* find)
{
  while(explore.size() > 0) // explore if nodes in queue
  {
    int min = INT_MAX;
    Actor* curr;
    int count = -1;
    int counter;
    for(vector<pair<int, Actor*>>::iterator itr = explore.begin(); 
        itr != explore.end(); itr++)
    {
      count++;
      if((*itr).first < min)
      {
        min = (*itr).first;
        curr = (*itr).second;
        counter = count;
      }
    }
    explore.erase(explore.begin() + counter);
    curr->done == true;
    if(curr == find) // if we found actor stop
    {
      break;
    }
    for(pair<Actor*, Movie*> a: curr->connections) 
    // explore all connections of current actor
    {
      if(!(a.first->done))
      {
        int c = curr->dist + 1 + (2015 - (a.second)->year);
        if(c < (a.first)->dist)
        {
          (a.first)->prev = curr;
          (a.first)->dist = c;
          explore.push_back(make_pair(c, a.first));
          
        }
      }
    }
  }

}

