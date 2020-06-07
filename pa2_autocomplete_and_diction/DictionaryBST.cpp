/*
* Name: Megan Chu
* PID: A12814536
* Date: April 21, 2017
* CSE 100 PA3 C++ Autocomplete
*/

#include "util.h"
#include "DictionaryBST.h"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
  std::pair<std::set<std::string>::iterator,bool> isNew = bst.insert(word);
  return isNew.second; // true is new insert, false if duplicate
 }

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
  std::set<std::string>::iterator itr = bst.find(word);
  if(itr != bst.end()) // if iterator does not point past the end
  {
    return true; // element is in dictionary
  }
  return false;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}
