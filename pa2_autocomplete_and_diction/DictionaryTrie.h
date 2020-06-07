/*
* Name: Megan Chu
* PID: A12814536
* Date: April 21, 2017
* CSE 100 PA3 C++ Autocomplete
*/

/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef NODE
#define NODE

#include <vector>
#include <string>
#define CHARACTERS 27
class Node // Node for Multiway Trie
{
  public:
    bool word = false;  // Node's "word" label
    unsigned int frequency; // only exists if word is true, gives frequency
    Node* letters[CHARACTERS]; // index 0 = 'a', index 1 = 'b', etc.
    Node(); // Node constructor
};
#endif


#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>

/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();


private:
  Node* root = new Node(); // starting node of Multiway Trie

  /* will recursively delete Nodes by traversing children then deleting */
  void helpDestruct(Node *curr); 

  /* will return the index in array for a specific letter */
  int index(char c) const; 

  /* will recursively find possible completed words from a prefix */
  std::vector<std::pair<std::string, int>> completionHelper(Node* curr, 
                                           std::string incWord);
};

#endif // DICTIONARY_TRIE_H



