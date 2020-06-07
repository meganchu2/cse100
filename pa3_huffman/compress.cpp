/*
* Name: Megan Chu
* PID: A12814536
* Date: May 10, 2017
* CSE 100 PA3 C++ Huffman
*/

#include<iostream>
#include<ostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<set>
#include<cstdlib>
#include "BitInputStream.h"
#include "BitOutputStream.h"
#include "HCTree.h"
#define INPUT 3
#define IN 1
#define OUT 2
#define BYTES 256

typedef unsigned char byte;

using namespace std;


/*
 * loads bytes and creates a Huffman coding tree
  * Parameters: int argc, the number of arguments to take
 *             char** argv, with the input and output files
 */
int main(int argc, char** argv)
{
  if(argc != INPUT) // need input and output files as arguments
  {
    cout << "Invalid input" << endl;
    return -1;
  }
  
  int numBytes = 0; // store total bytes read from input
  int unique = 0; // store unique bytes in input
  vector<unsigned int> freqs(BYTES, 0); // initialize 256 indexes with value 0
  
  cout << "Reading from file " << argv[IN] << "... " << flush;
  ifstream toRead; // tally frequencies of bytes in input file
  toRead.open(argv[IN], ios::binary);
  if (toRead.fail()) 
  {
    toRead.close();
    return -1;
  }
  else
  {
    byte readByte;
    while (true) // read bytes until end of file
    {
      readByte = toRead.get();
     // toRead.read((char*)&readByte, sizeof(readByte)); // read bytes (char)
      if(toRead.eof()) 
      {
        cout << "done." << endl;
        break;
      }
      numBytes++; // increment for every byte read
      if(freqs[(int)readByte] == 0)
      {
        unique++; // increment for every new byte read
      }
      freqs[(int)readByte]++; // tally frequencies of each char     
    }
    toRead.close();
  }
  cout << "Found " << unique << " unique symbols in input file of size "
       << numBytes << " bytes." << endl;


  cout << "Building Huffman code tree... ";
  // Huffman tree to encode characters
  HCTree coder;  
  coder.build(freqs);
  cout << "done." << endl;

  // Huffman tree to encode header for small output
  vector<unsigned int> freqsH(BYTES, 1);
  HCTree header;
  header.build(freqsH);

  ofstream toWrite; // create output file and add header
  BitOutputStream bitWrite(toWrite);
  toWrite.open(argv[OUT], fstream::out | fstream::trunc | fstream::binary);
  if(toWrite.fail())
  {
    toWrite.close();
    return -1;
  } 
  else
  {
    toWrite.write((char*)&numBytes, sizeof(numBytes));
    // need numBytes to avoid reading padded 0s
    toWrite.write((char*)&unique, sizeof(unique));
    for(int i: freqs) // for every index in freqs
    {
      header.encode((byte)i, bitWrite); // write frequencies for indexes 
    }
  }
  
  toRead.open(argv[IN], ios::binary); // encode bytes and add to outfile
  if (toRead.fail()) 
  {
    toRead.close();
    return -1;
  }
  else
  {
    cout << "Writing to file " << argv[OUT] << "... ";
    byte readByte;
    while (true) // read bytes until end of file
    {
      readByte = toRead.get();
      if (toRead.eof()) 
      {
        cout << "done." << endl;
        break;
      }
      coder.encode(readByte, bitWrite); 
      // get encoded bits for byte and write to outfile
    }
    bitWrite.flush(); // to complete any incomplete bytes
    cout << "Output file has size " << toWrite.tellp() << " bytes." << endl;
    cout << "Compression ratio: " 
         << (double)toWrite.tellp()/numBytes << endl;
    toRead.close();
  }

  toWrite.close();
  return 0;
}
  

