/*
* Name: Megan Chu
* PID: A12814536
* Date: May 10, 2017
* CSE 100 PA3 Huffman
*/

#include <iostream>
#include "HCNode.h"

typedef unsigned char byte;

using namespace std;

/** Less-than comparison, so HCNodes will work in std::priority_queue
 *  We want small counts to have high priority.
 *  And we want to break ties deterministically.
 */
bool HCNode::operator<(const HCNode& other)
{
  if(count < other.count)
  {
    return true;
  }
  return false;
}



