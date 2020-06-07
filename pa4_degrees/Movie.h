/*
* Name: Megan Chu
* PID: A12814536
* Date: May 25, 2017
* CSE 100 PA4 C++ Kevin Bacon
*/

#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include "Actor.h"

using namespace std;

/**
 * defines Actor nodes, one for each actor, used to know which actor is in 
 * which movie and who has connections to who
 */
class Actor;

/** 
 * defines movie objects, one for each unique movie
 */
class Movie
{
public:
    string title;
    int year;
    string key;
    vector<Actor*> actors; // list of actors in movie
    unordered_map<string, Actor*> actorSet;
    Movie* movieRoot; 
    bool merged = false;  

    Movie() : title(0) { } // default constructor

    Movie(string title, int year) // constructor with title and year
        : title(title), year(year) { }
};

#endif // MOVIE_H
