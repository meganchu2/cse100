/*
* Name: Megan Chu
* PID: A12814536
* Date: May 10, 2017
* CSE 100 PA3 Huffman
*/

#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"
#include "HCTree.h"

using namespace std;


/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<unsigned int>& freqs)
{
  queue<HCNode*> roots; // store nodes of symbols that occurred in input
  int maxFreq = 0; // store max frequency to create priority queue
  for(int i = 0; i < freqs.size(); i++)
  {
    if(freqs[i] > 0) // create node only for bytes that appear in input
    {
      leaves[i] = new HCNode(freqs[i], (byte)i);
      if(freqs[i] > maxFreq) // update max frequency if needed
      {
        maxFreq = freqs[i];
      }
    }
  }

  for(int i = 1; i <= maxFreq; i++) // push leaves starting with min freq
  {
    for(int j = 0; j < leaves.size(); j++)
    {
      if(leaves[j] && leaves[j]->count == i)
      {
        roots.push(leaves[j]); // push all leaves with this count onto list
      }
    }
  } // all leaves now in queue with min freq leaves to be popped first
  
  while(1 < roots.size()) 
  // we need 2 subtrees/roots to put them together
  {
    HCNode* min1 = roots.front(); // store min freq bytes/nodes/subtrees
    roots.pop();
    HCNode* min2 = roots.front();
    roots.pop();

    HCNode* shareRoot = new HCNode(min1->count + min2->count, 0); 
    // create shared root for 2 min freq bytes
    shareRoot->c0 = min1;
    shareRoot->c1 = min2;
    min1->p = shareRoot;
    min2->p = shareRoot;

    // need to place shareRoot in roots queue in correct order
    bool shareInserted = false;

    for(int i = 0; i < roots.size(); i++)
    // loop through queue to find right place for new subtree
    {
      if(roots.front()->count <= shareRoot->count)
      // subtree should be behind all roots less than or equal to it
      // this will give us shorter height and faster runtime
      {
        roots.push(roots.front());
        roots.pop();
      }
      else // next node in roots is greater than new subtree
      {
        roots.push(shareRoot);
        shareInserted = true;
        roots.push(roots.front());
        roots.pop();
      }
    }
    if(!shareInserted) // new subtree has greatest count/frequency
    {
      roots.push(shareRoot);
    }
    
  } // only one tree with all leaves in roots
  root = roots.front();
}


/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const
{
  vector<int> bitStream; // store stack of bits encoding byte symbol
  HCNode* curr = leaves[(int)symbol]; // start from leaf node for byte symbol
  while(curr != root) // traverse until root
  {
    if((curr->p)->c0 == curr) // 0 path
    {
      bitStream.push_back(0);
    }
    else // 1 path
    {
      bitStream.push_back(1);
    }
    curr = curr->p;
  } // we have stack of bits to output

  while(bitStream.size() > 0) // pop all bits from stack and write to output
  {
    out.writeBit(bitStream.back());
    bitStream.pop_back();
  }
}

/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode(byte symbol, ofstream& out) const
{
  vector<int> bitStream; // store stack of bits encoding byte symbol
  HCNode* curr = leaves[(int)symbol]; // start from leaf node for byte symbol
  while(curr != root) // traverse until root
  {
    if((curr->p)->c0 == curr) // 0 path
    {
      bitStream.push_back(0);
    }
    else // 1 path
    {
      bitStream.push_back(1);
    }
    curr = curr->p;
  } // we have stack of bits to output

  while(bitStream.size() > 0) // pop all bits from stack and write to output
  {
    out << bitStream.back();
    bitStream.pop_back();
  }
}


/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const
{
  unsigned int nextBit;
  HCNode* curr = root; // start at root
  while(curr != leaves[curr->symbol])
  // traverse by bits until we reach a node in leaves
  {
    nextBit = in.readBit(); // read bits from BitInputStream
    if(nextBit == 0) // c0 child
    {
      curr = curr->c0;
    }
    else // c1 child
    {
      curr = curr->c1;
    }
  }
  return curr->symbol; // return ASCII key of symbol for leaf node
}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode(ifstream& in) const
{
  byte b;
  HCNode* curr = root; // start at root
  while(curr != leaves[curr->symbol])
  // traverse by bits until we reach a node in leaves
  {
    b = in.get(); // read bytes (char)
    if(in.eof()) 
    {
      cout << "End of File" << endl;
      break;
    }
    if(b == '0') // c0 child
    {
      curr = curr->c0;
    }
    else // c1 child
    {
      curr = curr->c1;
    }
  }
  return curr->symbol; // return symbol of leaf node
}

/**
 * destructor for Huffman tree
 */
HCTree::~HCTree()
{
   deleteHelper(root); // recursively delete all subtrees
   root = NULL;
}

/**
 * helper method for Huffman tree deconstructor
 * Parameter: HCNode pointer to current node
 */
void HCTree::deleteHelper(HCNode* curr)
{
  if(curr) // if memory was allocated for curr
  {
    deleteHelper(curr->c0); // delete 0 path subtree
    deleteHelper(curr->c1); // delete 1 path subtree
    delete curr; // delete this node
  }
}
