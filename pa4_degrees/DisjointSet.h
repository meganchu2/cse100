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

class DisjointSet
{
protected:
   

public:
    Actor* sentinel;
    int size = 0;

    DisjointSet(void);
    void increment();
    void addSet(vector<Actor*> actors, Actor* a);

