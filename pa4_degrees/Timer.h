/*
* Name: Megan Chu
* PID: A12814536
* Date: April 21, 2017
* CSE 100 PA3 C++ Autocomplete
*/

#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <vector>
#include <string>
#include <iostream>

using std::istream;

class Timer{
private:
    /* start the timer */
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    
public:
    Timer(void);
    /*
     * Function called when starting the timer.
     */
    void begin_timer();
    
    /*
     * Function called when ending the timer. Returns duration in nanoseconds
     * PRECONDITION: begin_timer() must be called before this function
     */
    long long end_timer();
       
};


#endif //TIMER_H
