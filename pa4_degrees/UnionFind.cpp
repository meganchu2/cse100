/*
 * UnionFind.cpp
 * Author: Megan Chu
 * Date: May 25, 2017
 *
 * !!!!!!READ: doesn't find actors in set correctly but merges all 
 * actors in movie sets by year correctly!!!!!
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
#include "UnionFind.hpp"
#include "Actor.h"
#include "Movie.h"
#define YEAR 2015
#define NF 9999

using namespace std;

UnionFind::UnionFind(void) {} // default constructor


/** 
 * Load the graph from a tab-delimited file of actor->movie relationships.
 *
 * in_filename - input filename
 * use_weighted_edges - if true, compute edge weights as 
 * 1 + (2015 - movie_year), otherwise all edge weights will be 1
 *
 * return true if file was loaided sucessfully, false otherwise
 */
bool UnionFind::loadFromFile(const char* in_filename)
{
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
    movieLink->key = movie_key;
    sets.insert(make_pair(actor_name, newAct));


    for(vector<Actor*>::iterator aItr = 
        ((movieLink)->actors).begin(); 
        aItr != ((movieLink)->actors).end(); aItr++) // every actor in movie
    {
      (newAct->connections).push_back(make_pair(*aItr, movieLink));
      ((*aItr)->connections).push_back(make_pair(newAct, movieLink));
      edges += 2; // undirected edges
    }
    (newAct->movies).push_back(movieLink);
    // put Actor into set
    (movieLink->actorSet).insert(make_pair(actor_name, newAct));
    movieLink->movieRoot = NULL;
    // point to self if only actor

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
void UnionFind::clearEdges()
{
  for(unordered_map<string, Actor*>::iterator itr = actors.begin(); 
      itr != actors.end(); itr++) // reset all searched nodes
  {
    ((itr->second)->connections).clear();
  }
  edges = 0;
}



/**
 *
 */
void UnionFind::find(const char* load, const char* in_filename, 
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
      out << actor1Name << "\t" << actor2Name << "\t" << NF << endl;
      continue;
    }

    Actor* actor1 = (actors.find(actor1Name))->second; // get start actor
    Actor* actor2 = (actors.find(actor2Name))->second; // get end actor
    int recentYear = minYear;
    merge(recentYear, actor1, actor1);
    cout << recentYear << endl;
    while(rootFinder(actor1) != rootFinder(actor2)) // actors not in same set
    {
      if(recentYear == YEAR)
      {
        recentYear = NF;
        break;
      }
      recentYear++;
      merge(recentYear, actor1, actor1);
    }
    out << actor1Name << "\t" << actor2Name << "\t" << recentYear << endl;
    sets.clear();
    for(pair<string, Actor*> m: actors)
    {
      (m.second)->up = NULL;
    //  (m.second)->merged = false;
      sets.insert(pair<string, Actor*>(m.first, m.second));
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
 *
 */
//bool UnionFind::sameSet(Actor* a1, Actor* a2, int max)
//{
 // for(Movie* m: a1->movies)
  //{
   // Movie* root = rootFinder(m);
    //for(Movie* m2: a2->movies)
    //{
     // Movie* root2 = rootFinder(m2);
      //if(m == m2 && m->year <= max && m2->year <= max)
     // {
     //   return true;
     // }
  //  }
 // }
 // return false;
//}

Actor* UnionFind::rootFinder(Actor* curr)
{
  if(!curr->up)
  {
    return curr;
  }
  Actor* temp = rootFinder(curr->up);
  curr->up = temp;
  return temp;
}

/**
 *
 */
void UnionFind::merge(int max, Actor* a, Actor* curr)
{
  for(pair<Actor*, Movie*> m: curr->connections)
  {
    if((m.second)->year <= max && rootFinder(m.first) != a) 
    // movies for max year will be sentinel
    {
      (m.first)->up = a;
      merge(max, a, m.first);
    } 
  }
         
}


