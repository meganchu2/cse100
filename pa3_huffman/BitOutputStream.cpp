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
#include "BitOutputStream.h"
#define BIT 7

typedef unsigned char byte;

using namespace std;


/** 
 * send bitwise buffer to the output stream, and clear bitwise buffer
 */
void BitOutputStream::flush() 
{
  out.put(buf); // write the bitwise buffer to the ostream
  out.flush(); // flush the ostream (optional, slower to do it here)
  buf = 0; // clear the bitwise buffer
  nbits = 0; // bitwise buffer is cleared, so there are 0 bits in it
}


/**
 * write bit to the bitwise buffer
 * Parameters: unsigned int to write to position in byte
 */
void BitOutputStream::writeBit(unsigned int bit) 
{
  // flush the bitwise buffer if it is full
  if(nbits == (BIT + 1)) 
  {
    flush();
  }

  // set the next open bit of the bitwise buffer to 'bit'
  buf = buf & ~(1 << (BIT-nbits)); // clear nbitsth bit in byte
  buf = buf | (bit << (BIT-nbits)); // set position specified by nbits to bit
  
  // increment the number of bits in our bitwise buffer
  nbits++;
}

