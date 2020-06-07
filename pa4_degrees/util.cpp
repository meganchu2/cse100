/*
* Name: Megan Chu
* PID: A12814536
* Date: April 21, 2017
* CSE 100 PA3 C++ Autocomplete
*/

#include <iostream>
#include <sstream>
#include "util.h"

using std::istream;
using std::endl;
using std::cout;
using std::istringstream;
using std::string;
using std::vector;

/*
 * Starts the timer. Saves the current time.
 */
void Timer::begin_timer()
{
    
    start = std::chrono::high_resolution_clock::now();
}

/*
 * Ends the timer. Compares end time with the start time and returns number 
 * of nanoseconds
 */
long long Timer::end_timer()
{
    
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    end = std::chrono::high_resolution_clock::now();
    
    return (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

/* Parse a line from a dictionary file.  This line has the frequency as 
 * the first string, and the "word" (which may be a multi-word phrase)	
 * as the rest of the string.  This function will remove the frequency,
 * leaving "word".  It assumes the first set of characters before the 
 * space is the number, and will always remove it.  If there is no space
 * before the end of the line, it will not change the string.
 *
 * Input: a line from a dictionary file.  This line will be modified.
 */
unsigned int Utils::stripFrequency(string& line)
{
    // Count the number of characters past the first space
    int count = 0;
    string::iterator last = line.end();
    for (string::iterator it = line.begin(); it != last; ++it) {
        count++;
        if (*it == ' ') {
            break;
        }
    }
    unsigned int freq = std::stoi(line.substr(0, count));
    line.erase(0, count);
    return freq;
}

