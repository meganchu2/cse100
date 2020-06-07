/*
* Name: Megan Chu
* PID: A12814536
* Date: May 25, 2017
* CSE 100 PA4 C++ Kevin Bacon
*/

#ifndef ACTOR_H
#define ACTOR_H

#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

/** 
 * defines movie objects, one for each unique movie
 */
class Movie;

/**
 * defines Actor nodes, one for each actor, used to know which actor is in 
 * which movie and who has connections to who
 */
class Actor
{
public:
    string name;
    vector<pair<Actor*, Movie*>> connections; 
    // connections to other actors with connecting movie
    vector<Movie*> movies; // projects actor was in
    Actor* prev; // previous actor in shortest path
    int dist = INT_MAX;
    bool done;
    Actor* up;

    Actor() : name(0) { } // default constructor

    Actor(string person) // constuctor with actor name
        : name(person) { }

};

#endif // ACTOR_H
