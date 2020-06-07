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
#define INPUT 5
#define ACTORS 1
#define PAIRS 2
#define OUTPUT 3
#define UFIND 4

using namespace std;

DisjointSet::DisjointSet(void){} // default constructor

void DisjointSet::increment()
{
  size++;
}

void DisjointSet::addSet(vector<Actor*> actors, Actor* a)
{
  if(size < actors.size()) // this set smaller
  {
    bool first = true;
   
    for(vector<Actor*>::iterator itr = actors.begin();
            itr != actors.end(); itr++)
    {
      if(*itr != a)
      {
        if(first)
        {
           sentinel->up = *itr;
           sentinel = sentinel->up;
           size++;
           first = false;
        }
        else
        {
          (*itr)->up = sentinel;
          size++;
        }
      }
    }
  }
  else // other set smaller
  {
    for(vector<Actor*>::iterator itr = actors.begin();
        itr != actors.end(); itr++)
    {
      if(*itr != a)
      {
        (*itr)->up = sentinel;
        size++;
      }
    }

  }
}

