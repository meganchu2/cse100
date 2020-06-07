/*
 * UnionFind.cpp
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
#include "Actor.h"
#include "Movie.h"
#define YEAR 2015

using namespace std;

/**
 * class that contains information of all the nodes for actors and their 
 * connections
 */
class UnionFind
{
protected:
    unordered_map<string, Actor*> actors; // store all actor nodes
    unordered_map<string, Movie*> movies; // store all movies
    int edges = 0; // store num connections between actors
    unordered_map<string, Actor*> sets; // map of disjoint sets

public:
    UnionFind(void); // default constructor

    /** 
     * Load the graph from a tab-delimited file of actor->movie 
     * relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 
     * 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename);
    void clearEdges();
    void find(const char* load, const char* in_filename, 
              const char* out_filename);
    void merge(int max, Actor* a, Actor* curr);
    bool sameSet(Actor* a1, Actor* a2, int max);
    Actor* rootFinder(Actor* curr);
    void addSet(Actor* act, int max, Movie* currM);
};
