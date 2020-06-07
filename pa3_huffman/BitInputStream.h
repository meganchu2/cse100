/*
* Name: Megan Chu
* PID: A12814536
* Date: May 17, 2017
* CSE 100 PA3 Huffman
*/

#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H

#include<iostream>
#include<fstream>
#include<set>
#include<cstdlib>
#include<cstdint>
#define BIT 7

typedef unsigned char byte;

using namespace std;

class BitInputStream 
{
  private:
    byte buf; // bitwise buffer (one byte)
    int nbits; // number of bits that have been read from bitwise buffer
    istream & in; // reference to the the C++ input stream
    bool eof = false;

  public:
    // constructor: assign 'in' to 'is', 'buf' to 0, and 'nbits' to 8
    BitInputStream(istream & is) : in(is), buf(0), nbits(BIT + 1) {}

    // fill the bitwise buffer by reading one byte from the input stream
    void fill();
   
    // read bit from the bitwise buffer
    unsigned int readBit();
};

#endif // BITINPUTSTREAM_H
