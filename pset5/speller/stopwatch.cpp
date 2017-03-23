/**
 * Implements a stopwatch.
 */

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "stopwatch.h"

#include <iostream>
#include <iomanip>
using namespace std;

#define DEBUG

enum times {
    TIME_LOAD = 0, TIME_CHECK, TIME_SIZE, TIME_UNLOAD, TIME_TOTAL
};

// Returns number of seconds between b and a.
double Stopwatch::calculate() {
#ifdef DEBUG
    //tagging(TAG, "calculate");
#endif

    const struct rusage *b = &before;
    const struct rusage *a = &after;
    
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
    return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
             (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
            ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
             (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
            / 1000000.0);
    }
}

#ifdef DEBUG
// debug info
void Stopwatch::tagging(const char* NAME) {
    cout<<TAG<<" === "<<NAME<<" === "<<endl;
}
#endif

// constructor for debug
Stopwatch::Stopwatch() {
#ifdef DEBUG
    //tagging("Stopwatch()");
#endif
};

// destructor  for debug
Stopwatch::~Stopwatch() {
#ifdef DEBUG
    //tagging("~Stopwatch()");
#endif
};

// get results for report them
double Stopwatch::getResults(int index) {
#ifdef DEBUG
    //tagging(TAG, "getResults");
#endif    
    return results[index];
}

// start a stopwatch
void Stopwatch::start() {
#ifdef DEBUG
    //tagging(TAG, "start");
#endif
    getrusage(RUSAGE_SELF, &before);
}

// stop a stopwatch
void Stopwatch::stop() {
#ifdef DEBUG
    //tagging(TAG, "stop");
#endif
    getrusage(RUSAGE_SELF, &after);
}

// determining the time difference
int Stopwatch::calculate(int index){
#ifdef DEBUG
    //tagging(TAG, "calculate(int index)");
#endif

    if(TIME_TOTAL == index){
        for(int i = TIME_TOTAL - 1 ; i >= 0; i-- ){
            // total result of all array elements
            results[TIME_TOTAL] += results[i];
        }
    }
    else {
        // fixing different measurements
        results[index] += calculate();
    }
    return 0;
}
