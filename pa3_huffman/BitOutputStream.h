/*
* Name: Megan Chu
* PID: A12814536
* Date: May 17, 2017
* CSE 100 PA3 Huffman
*/

#ifndef BITOUTPUTSTREAM_H
#define BITOUTPUTSTREAM_H

#include<iostream>
#include<fstream>
#include<set>
#include<cstdlib>
#include<cstdint>
#define BIT 7

typedef unsigned char byte;

using namespace std;


class BitOutputStream 
{
  private:
    unsigned char buf; // bitwise buffer (one byte)
    int nbits; // number of bits that have been written to the bitwise buffer
    ostream & out; // reference to the bytewise C++ output stream)

  public:
    // constructor: assign 'out' to 'os', 'buf' to 0, and 'nbits' to 0
    BitOutputStream(ostream & os) : out(os), buf(0), nbits(0) {}

    // send bitwise buffer to the output stream, and clear bitwise buffer
    void flush();

    // write bit to the bitwise buffer
    void writeBit(unsigned int bit);

};

#endif // BITOUTPUTSTREAM_H
