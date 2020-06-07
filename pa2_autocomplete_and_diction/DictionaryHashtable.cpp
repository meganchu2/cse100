/*
* Name: Megan Chu
* PID: A12814536
* Date: April 21, 2017
* CSE 100 PA3 C++ Autocomplete
*/

#include "util.h"
#include "DictionaryHashtable.h"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
  std::unordered_set<std::string>::const_iterator itr = hashT.find(word);
  hashT.insert(word);
  if(itr == hashT.end()) // element not found before insert
  {
    return true; // new insert
  }
  return false; // element was found before insert, so this is duplicate
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
  std::unordered_set<std::string>::const_iterator itr = hashT.find(word);
  if(itr != hashT.end()) // element was found
  {
    return true;
  }
  return false; // element not found
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){}
