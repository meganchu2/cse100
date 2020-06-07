/*
* Name: Megan Chu
* PID: A12814536
* Date: May 17, 2017
* CSE 100 PA3 Huffman
*/

#include<iostream>
#include<fstream>
#include<set>
#include<cstdlib>
#include<cstdint>
#include "BitInputStream.h"
#define BIT 7

typedef unsigned char byte;

using namespace std;

/**
 * fill the bitwise buffer by reading one byte from the input stream
 */
void BitInputStream::fill() 
{
  buf = in.get(); // read one byte from istream to bitwise buffer
  nbits = 0;      // no bits have been read from bitwise buffer
}


/**
 * read bit from the bitwise buffer
 */
unsigned int BitInputStream::readBit() 
{
  // fill bitwise buffer if there are no more unread bits
  if(nbits == (BIT + 1)) 
  {
    fill();
  }
  // get the next unread bit from the bitwise buffer
  unsigned int nextBit = (buf & (1 << (BIT-nbits))) >> (BIT-nbits); 
  // read bit at nbit position from left of byte

  // increment the number of bits we have read from the bitwise buffer
  nbits++;

  // return the bit we just read
  return nextBit;
}
