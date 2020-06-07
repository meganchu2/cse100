/*
 * ActorGraph.h
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can 
 * use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include <ostream>
#include <fstream>
#include <queue>
#include <utility>
#include <unordered_map>
#include "Actor.h"
#include "Movie.h"

using namespace std;

/**
 * class that contains information of all the nodes for actors and their 
 * connections
 */
class ActorGraph 
{
protected:
    unordered_map<string, Actor*> actors; // store all actor nodes
    unordered_map<string, Movie*> movies; // store all movies
    int edges = 0; // store num connections between actors
    bool weighted;

public:
    ActorGraph(void); // default constructor

    /**
     * compute the paths between two actors given by a tab-delimited file of
     * actor->actor relationships to compute
     * Parameters: in_filename, input file of relationships to compute
     *             out_filename, output file to write path
     */               
    void computePath(const char* in_filename, const char* out_filename);

    /**
     * helper method to find shortest path using a queue
     * Parameters: explore, queue of actors to compare to target
     *             find, target actor to find
     */  
    bool pathHelper(queue<Actor*> explore, Actor* find);

    /**
     * helper method to find shortest path using a queue for weighted graph
     * Parameters: explore, queue of actors to compare to target
     *             find, target actor to find
     */  
    void weightHelper(vector<pair<int, Actor*>> explore, Actor* find);

    /**
     * helper method to recursively print shortest path
     * Parameters: out, output stream to write to
     *             curr, current actor info to print
     *             end, last actor infor to print
     */ 
    void printHelper(ofstream& out, Actor* curr, Actor* end);
     
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
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);

    bool loadComponents(const char* in_filename);

    void addEdges(int year);
 
    void actorConnections(const char* in_filename, const char* out_filename);
 
    void clearEdges();
  
};


#endif // ACTORGRAPH_H
