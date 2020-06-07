/*
* Name: Megan Chu
* PID: A12814536
* Date: May 4, 2017
* CSE 100 PA3 C++ Autocomplete
*/

#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define MIN 1
#define STEP 2
#define ITERATIONS 3
#define DF 4
#define SIZE 5
#define NEXT 100
#define TIMES 200

using namespace std;


/*
 * loads words to simulate hash table (no real table exists), keeps track 
 * of how many hits an index gets and how many positions in table have each 
 * specific number of hits
 * Parameters: int argc, the number of arguments to take
 *             char** argv, with the dictionary file and number words to load
 */
int main(int argc, char** argv)
{
  if(argc != SIZE) // need 4 arguments
  {
    cout << "Invalid number of inputs" << endl;
    return -1;
  }

  int min = atoi(argv[MIN]); // get int value for min_size
  int step = atoi(argv[STEP]); // int value for step_size
  int iterations = atoi(argv[ITERATIONS]); // int value for num_iterations
  
  Timer time;
  
  // DictionaryBST
  cout << "\nDictionaryBST" << endl;
  for(int i = 0; i < iterations ; i++) // repeat for specified num iterations
  {
    // initialize empty bst, time and vector of words to find
    DictionaryBST* bst = new DictionaryBST();
    int totalTime = 0;
    vector<string> toFind;

    // load words into bst
    std::filebuf db;
    if(db.open(argv[DF], std::ios::in))
    {
      std::istream dictionary(&db);
      Utils::load_dict(*bst, dictionary, min + step*i);
      Utils::load_vector(toFind, dictionary, NEXT);
      db.close();
    }

    // repeat search time calculation 200 times for accurate average
    for(int i = 0; i < TIMES; i++)
    {
      vector<string>::iterator itr = toFind.begin();
      time.begin_timer(); // start timer for this word
      while(itr != toFind.end())
      {
        (*bst).find(*itr);
        ++itr;
      }
      totalTime += time.end_timer(); // add time to find this word
    }
    cout << min + step*i << "\t" << totalTime/TIMES << endl;
    delete bst; // free memory for hash table
  }

  // DictionaryHashtable
  cout << "\nDictionaryHashtable" << endl;
  for(int i = 0; i < iterations ; i++) // repeat for specified num iterations
  {
    // initialize empty hash table, time and vector of words to find
    DictionaryHashtable* ht = new DictionaryHashtable();
    int totalTime = 0;
    vector<string> toFind;

    // load words into hash table
    std::filebuf db;
    if(db.open(argv[DF], std::ios::in))
    {
      std::istream dictionary(&db);
      Utils::load_dict(*ht, dictionary, min + step*i);
      Utils::load_vector(toFind, dictionary, NEXT);
      db.close();
    }

    // repeat search time calculation 200 times for accurate average
    for(int i = 0; i < TIMES; i++)
    {
      vector<string>::iterator itr = toFind.begin();
      time.begin_timer(); // start timer for this word
      while(itr != toFind.end())
      {
        (*ht).find(*itr);
        ++itr;
      }
      totalTime += time.end_timer(); // add time to find this word
    }
    cout << min + step*i << "\t" << totalTime/TIMES << endl;
    delete ht; // free memory for trie
  }

  // Dictionary Trie
  cout << "\nDictionaryTrie" << endl;
  for(int i = 0; i < iterations ; i++) // repeat for specified num iterations
  {
    // initialize empty hash table, time and vector of words to find
    DictionaryTrie* dt = new DictionaryTrie();
    int totalTime = 0;
    vector<string> toFind;

    // load words into hash table
    std::filebuf db;
    if(db.open(argv[DF], std::ios::in))
    {
      std::istream dictionary(&db);
      Utils::load_dict(*dt, dictionary, min + step*i);
      Utils::load_vector(toFind, dictionary, NEXT);
      db.close();
    }
    
    // repeat search time calculation 200 times for accurate average
    for(int i = 0; i < TIMES; i++)
    {
      vector<string>::iterator itr = toFind.begin();
      time.begin_timer(); // start timer for this word
      while(itr != toFind.end())
      {
        (*dt).find(*itr);
        ++itr;
      }
      totalTime += time.end_timer(); // add time to find this word
    }
    cout << min + step*i << "\t" << totalTime/TIMES << endl;
    delete dt; // free memory so no leaks
  }

  return 0;
} // end of main
