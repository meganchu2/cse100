/*
* Name: Megan Chu
* PID: A12814536
* Date: May 10, 2017
* CSE 100 PA3 C++ Huffman
*
* 
*/

#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include<cstdint>
#include "HCNode.h"
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
 * decodes input file using Huffman coding tree 
 * Parameters: int argc, the number of arguments to take
 *             char** argv, with the input and output files
 */
int main(int argc, char** argv)
{
  if(argc != INPUT) // need input and output files as arguments
  {
    cout << "Invalid input" << endl;
  }

  int numBytes; // store number of bytes to read/output
  int unique; // store number of unique bytes we will read/output
  vector<unsigned int> freqs(BYTES, 0); // initialize 256 indexes with value 0

  // create header tree to read header
  HCTree header;
  vector<unsigned int> freqsH(BYTES, 1);
  header.build(freqsH);

  cout << "Reading header from file " << argv[IN] << "... ";
  ifstream toRead; // tally frequencies of bytes in input file
  BitInputStream bitRead(toRead);
  toRead.open(argv[IN], fstream::in | fstream::binary);
  if (toRead.fail()) 
  {
    toRead.close();
  }
  else
  {
    toRead.read((char*)&numBytes, sizeof(numBytes));
    toRead.read((char*)&unique, sizeof(unique));
    int c;
    for(int i = 0; i < BYTES; i++) 
    {
      freqs[i] = header.decode(bitRead);    
    }
    cout << "done." << endl;
  }
  cout << "Uncompressed file will have " << unique 
       << " unique symbols and size " << numBytes << " bytes." << endl;

  cout << "Building Huffman code tree... ";
  HCTree decoder;
  decoder.build(freqs);
  cout << "done." << endl;

  ofstream toWrite; // create output file
  BitOutputStream bitWrite(toWrite);
  toWrite.open(argv[OUT], fstream::out | fstream::trunc | fstream::binary);
  if(toWrite.fail())
  {
    toWrite.close();
  } 
  else
  {
    int temp = numBytes;
    while (true) 
    {
      int i = decoder.decode(bitRead);
      if(toRead.eof() || temp == 0)
      {
        break;
      }
      temp--;
      byte c = (byte)i;
      toWrite << c;
      // decode bits for byte and write to outfile
    }
  }
  toRead.close();
  toRead.open(argv[IN], ios::binary | ios::ate);
  {
    cout << "Uncompression ratio: " << (double)numBytes/toRead.tellg() << endl;
  }
  toRead.close();
  toWrite.close();
}

