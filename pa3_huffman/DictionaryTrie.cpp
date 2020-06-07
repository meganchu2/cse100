/*
* Name: Megan Chu
* PID: A12814536
* Date: May 17, 2017
* CSE 100 PA3 C++ Huffman
*/

#include "util.h"
#include "DictionaryTrie.h"
#define NUM_ALPHA 27
#define SPACE 26


/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){}


/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) 
 * Parameters: string word to insert, and the int frequency of that word
 */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  std::string::iterator itr = word.begin();
  if(itr == word.end()) // empty string
  {
    return false;
  }

  Node* curr = root;
  while(itr != word.end())
  {
    int ind = index(*itr);
    if(!curr->letters[ind]) // no path with letter
    {
      curr->letters[ind] = new Node(); // create new path to new node
    }
    ++itr; // go to next letter
    curr = curr->letters[ind]; // go to next node   
    }
  } // we have traversed every letter in word
  if(curr->frequency < freq) // update to larger frequency
  {
    curr->frequency = freq;
  }
  if(curr->word) // if duplicate word
  {
    return false;
  }
  else // new word 
  {
    curr->word = true;
    return true;
  }  
}


/* Return true if word is in the dictionary, and false otherwise 
 * Parameters: string word to find in Trie
 */
bool DictionaryTrie::find(std::string word) const
{
  std::string::iterator itr = word.begin();
  Node* curr = root;
  while(itr != word.end()) // loop through letters in word
  {
    int ind = index(*itr);
    if(curr->letters[ind]) // if path with letter in word exists
    {
      ++itr; // get next letter
      curr = curr->letters[ind]; // go to next node
    }
    else // no path with letter
    {
      return false; // word not in tree
    }
  } // there is a path that contains letters of the word
  if(curr->word) // if last traversed path indicates a word
  {
    return true; // there is matching path and indicator for word
  }
  return false; // path does not indicate a word
}


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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string 
                         prefix, unsigned int num_completions)
{
  std::vector<std::string> words; // vector to return
  std::vector<std::pair<std::string, int>> allWords; // strings and freqencies
  std::string::iterator itr = prefix.begin();
  Node* curr = root;

  if(itr == prefix.end()) // prefix is empty string
  {
    std::cout << "Invalid Input. Please retry with correct input" 
              << std::endl;
    return words; // return empty vector
  }
  while(itr != prefix.end()) // loop through letters in prefix
  {
    int ind = index(*itr);
    if(ind < 0 || ind >= NUM_ALPHA) // invalid char
    {
      std::cout << "Invalid Input. Please retry with correct input" 
                << std::endl;
      return words; // return empty vector
    }
    if(curr->letters[ind]) // if path with letter in prefix exists
    {
      ++itr; // get next letter
      curr = curr->letters[ind]; // go to next node
    }
    else // no path with letter
    {
      return words; // prefix not in tree
    }
  } // there is a path that contains letters of the prefix
  
  allWords = completionHelper(curr, prefix);
  
  while(num_completions > 0 && allWords.size() != 0) // still words to return
  {
    int freq = 0; // highest frequency
    std::string word; // word with highest frequency
    int index = 0; // track index of word with highest frequency
    int iterIndex = 0; // track index of iterator

    for(std::vector<std::pair<std::string, int>>::iterator i = 
        allWords.begin(); i != allWords.end(); ++i, iterIndex++) 
    // loop through all words
    {
      if(std::get<1>(*i) > freq) // store information if frequency is greater
      {
        freq = std::get<1>(*i);
        word = std::get<0>(*i);
        index = iterIndex;
      }
    }
    words.push_back(word); // add highest frequency word to return list
    allWords.erase(allWords.begin() + index);
    num_completions--;
  }    
  return words;
}


/* helper method for predict completions that finds all words in the subtree 
 * of the prefix, and returns them 
 * Parameters: current Node in path, added char of all words so far
 */
std::vector<std::pair<std::string, int>> DictionaryTrie::completionHelper(
                                         Node* curr, std::string incWord)
{
  std::vector<std::pair<std::string, int>> words;
  for(int i = 0; i < NUM_ALPHA; i++) // loop through all paths
  {
    if(curr->letters[i]) // if there is path with this letter
    {
      std::string possWord;
      possWord.assign(incWord);
      if(i == SPACE)
      {
        possWord.push_back(' ');
      }
      else
      {
        possWord.push_back((char)(i + (int)'a')); // append path char to word
      }
      std::vector<std::pair<std::string, int>> moreWords = 
                                     completionHelper(curr->letters[i], 
                                     possWord); // traverse path
      words.insert(words.end(), moreWords.begin(), moreWords.end());
    }
  }
  if(curr->word) // if current node marks end of word, add to list
  {
    std::pair<std::string, int> newWord(incWord, curr->frequency);
    words.push_back(newWord);
  }
  return words;
}


/* Destructor */
DictionaryTrie::~DictionaryTrie()
{
  helpDestruct(root);
}

/**
 * recursively deletes nodes in Multiway Trie
 * Parameters: Node pointer to current node to delete, children are deleted 
 * before each node
 */
void DictionaryTrie::helpDestruct(Node* curr)
{
  for(int i = 0; i < NUM_ALPHA; i++)
  {
    if(curr->letters[i]) // if child exists, traverse subtree then delete
    {
      helpDestruct(curr->letters[i]);
    }
  }
  if(curr) // if this node exists, delete it
  {
    delete curr;
  }
}

/**
 * returns an int value for the index in array of a specific letter
 * Parameters: char c that represents a letter in the alphabet
 */
int DictionaryTrie::index(char c) const
{
  if(c == ' ')
  {
    return SPACE;
  }
  return (int)c - (int)'a';
}

/**
 * constructor for a Node that initializes all indexes to NULL
 */
Node::Node(void) 
{
  for(int i = 0; i < NUM_ALPHA; i++) 
  {
    letters[i] = NULL;
  }
}


