/*
* Name: Megan Chu
* PID: A12814536
* Date: May 4, 2017
* CSE 100 PA3 C++ Autocomplete
*/

#include<string>
#include<cstdlib>
#include<fstream>
#include <sstream>
#include<iostream>
#include "util.h"
#define tS 10
#define SIZE 3
#define NUM_WORDS 2

using std::vector;
using namespace std;


/*
 * http://stackoverflow.com/questions/8317508/hash-function-for-a-string
 * returns hash value based on ASII key sum of all char in string
 * Parameters: string str of string to calculate value for,
 *             int sz, size of hash table
 */
unsigned int hashFunc1(string str, int sz)
{
  unsigned int sum = 0;
  for(int i = 0; i < str.length(); i++)
  {
    sum += (int)str[i]; // summing ASII keys
  }
  return sum%sz; // mod table size
}


/*
 * thought up by myself based on hashFunc1
 * returns hash value based on ASII key sum of char in string with respect 
 * to position in string
 * Parameters: string str of string to calculate value for,
 *             int sz, size of hash table
 */
unsigned int hashFunc2(string str, int sz)
{
  unsigned int sum = 0;
  for(int i = 0; i < str.length(); i++)
  {
    sum += str[i]*(i+1); // summing ASII keys
  }
  return sum%sz; // mod table size
}


/*
 * loads words to simulate hash table (no real table exists), keeps track 
 * of how many hits an index gets and how many positions in table have each 
 * specific number of hits
 * Parameters: int argc, the number of arguments to take
 *             char** argv, with the dictionary file and number words to load
 */
int main(int argc, char** argv)
{
  /* // testing hashFunc1
  cout << "Testing hashFunc1 and hashFunc2" << endl;
  cout << hashFunc1("apple", tS) << endl;
  cout << hashFunc1("banana", tS) << endl;
  cout << hashFunc1("orange", tS) << endl;*/
  /* // testing hashFunc2
  cout << hashFunc2("apple", tS) << endl;
  cout << hashFunc2("banana", tS) << endl;
  cout << hashFunc2("orange", tS) << endl;*/

  if(argc != SIZE) // must have 2 arguments
  {
    cout << "Invalid number of inputs" << endl;
    return -1;
  }

  int num = atoi(argv[NUM_WORDS]); // int value for num words to insert 

  vector<string> words; // store words
  vector<int> hits1 (num + num, 0); // store num hits for each index
  vector<int> hits2 (num + num, 0);

  // load words into vector
  std::filebuf db;
  if(db.open(argv[1], std::ios::in))
  {
    std::istream dictionary(&db);
    Utils::load_vector(words, dictionary, num);
    db.close();
  }

  // generate num hits from hash values of words in vector
  for(string s: words)
  {
    int hV1 = hashFunc1(s, num + num);
    int hV2 = hashFunc2(s, num + num);
    hits1[hV1]++;
    hits2[hV2]++;
  }
  
  // get the largest number of hits (worst case steps) for both hash functions
  int max1 = hits1[0];
  int max2 = hits2[0];
  for(int i = 1; i < (num + num); i++)
  {
    if(hits1[i] > max1)
    {
      max1 = hits1[i]; // set max1 to greater hits
    }
    if(hits2[i] > max2)
    {
      max2 = hits2[i]; // set max2 to greater hits
    }
  }
  
  // print stats for hashFunc1
  cout << "Printing the statistics for hashFunction1 with hash table size " 
       << (num + num) << endl;
  cout << "#hits\t#slots receiving the #hits" << endl;

  for(int i = 0; i <= max1; i++) // print out #slots for each #hits
  {
    int slots = 0;
    for(int j = 0; j < (num + num); j++) // summing up slots with this #hits
    {
      if(hits1[j] == i)
      {
        slots++;
      }
    }
    if(slots > 0) // print out #hits and #slots if slots with this #hits
    {
      cout << i << "\t" << slots << endl;
    }
  }

  // calculate average steps using hash function 1
  double tAvg = 0;
  int tSlots = 0;
  for(int i = max1; i > 0; i--)
  {
    for(int j = 0; j < (num + num); j++)
    {
      if(hits1[j] == i)
      {
        tSlots++;
      }
    }
    tAvg += tSlots*i;    
  }

  // print average steps and worst steps for hashFunc1
  cout << "The average number of steps for a successful search for " 
       << "hash function 1 would be " << tAvg/(double)num << endl;
  cout << "The worst case steps that would be needed to find a word "
       << "is " << max1 << endl;

  // print stats for hashFunc2
  cout << "Printing the statistics for hashFunction2" << endl;
  cout << "#hits\t#slots receiving the #hits" << endl;

  for(int i = 0; i <= max2; i++)// print out #slots for each #hits
  {
    int slots = 0;
    for(int j = 0; j < (num + num); j++) // summing up slots with this #hits
    {
      if(hits2[j] == i)
      {
        slots++;
      }
    }
    if(slots > 0) // print out #hits and #slots if slots with this #hits
    {
      cout << i << "\t" << slots << endl;
    }  }

  // calculate average steps using hash function 2
  tAvg = 0;
  tSlots = 0;
  for(int i = max2; i > 0; i--)
  {
    for(int j = 0; j < (num + num); j++)
    {
      if(hits2[j] == i)
      {
        tSlots++;
      }
    }
    tAvg += tSlots*i;    
  }

  // print average steps and worst steps for hashFunc2
  cout << "The average number of steps for a successful search for " 
       << "hash function 1 would be " << tAvg/num << endl;
  cout << "The worst case steps that would be needed to find a word "
       << "is " << max2 << endl;

} // end of main
