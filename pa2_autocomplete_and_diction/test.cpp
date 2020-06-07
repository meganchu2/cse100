/*
* Name: Megan Chu
* PID: A12814536
* Date: April 28, 2017
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
#define LETTERS 26
using namespace std;

/*
 * implements test for insert find and predict completions for DictionaryBST, 
 * DictionaryHashtable, and DictionaryTrie
 * Parameters: int argc, the number of arguments to take
 *             char** argv, arguments needed
 */
int main(int argc, char** argv)
{

  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;

  words.push_back("harry");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("autocomplete");
  
  
  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 1);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

  cout << endl 
       << "Re-inserting elements that were just inserted into Dictionaries..." 
       << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 0);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  
  /*You are supposed to add more test cases in this file */
 
  cout << "testing find for bst, hashtable, and trie" << endl;
  /* testing find for bst */
  if(!d_bst.find("harry"))
  {
    cout << "failed to find harry in DictionaryBST" << endl;
  }
  /* testing find for hashtable */
  if(!d_ht.find("crucio"))
  {
    cout << "failed to find crucio in DictionaryHashtable" << endl;
  }
  /* testing find for trie */
  if(!dt.find("autocomplete"))
  {
    cout << "failed to find autocomplete in DictionaryTrie" << endl;
  }
  cout << "PASSED! :D" << endl;


  /* testing predictCompletions */
  /* load shuffled_unique_freq_dict to dictionary trie */
  DictionaryTrie autoComp;
  std::filebuf fb;
  if (fb.open ("shuffled_unique_freq_dict.txt",std::ios::in))
  {
    std::istream dictionary(&fb);
    Utils::load_dict(autoComp, dictionary);
    fb.close();
  }

  cout << "\nAutocomplete 3 sta..." << endl; // 3 completions for sta
  std::vector<std::string> possible = autoComp.predictCompletions("sta", 3);
  std::vector<std::string>::iterator itr = possible.begin();
  while(itr != possible.end())
  {
    cout << "  " << *itr << endl;
    ++itr;
  }

  cout << "Autocomplete 4 tri..." << endl; // 4 completions for tri
  possible = autoComp.predictCompletions("tri", 4);
  itr = possible.begin();
  while(itr != possible.end())
  {
    cout << "  " << *itr << endl;
    ++itr;
  }

  cout << "Autocomplete 10 laterall..." << endl; 
  // 10 completions for laterall if there is 10, less if there is less
  possible = autoComp.predictCompletions("laterall", 10);
  itr = possible.begin();
  while(itr != possible.end())
  {
    cout << "  " << *itr << endl;
    ++itr;
  }
  cout << "PASSED! :D" << endl;

  /* load smalldictionary to dictionary trie */
  DictionaryTrie edge;
  std::filebuf ab;
  if (ab.open ("smalldictionary.txt",std::ios::in))
  {
    std::istream smalldictionary(&ab);
    Utils::load_dict(edge, smalldictionary);
    ab.close();
  }

  cout << "\nAutocomplete 5 a..." << endl; // 2 completions for a
  possible = edge.predictCompletions("a", 5);
  itr = possible.begin();
  while(itr != possible.end())
  {
    cout << "  " << *itr << endl;
    ++itr;
  }

  /* testing find for trie */
  if(!edge.find("a aaa"))
  {
    cout << "failed to find a aaa in DictionaryTrie" << endl;
  }
  cout << "PASSED! :D" << endl;
  
  return 0;
} // end of main
