/**
 * Declares a stopwatch.
 */

#ifndef STOPWATCH_H
#define STOPWATCH_H

class Stopwatch {

private:
    
    static const int SIZE_OF_ARRAY = 5;
    double results[SIZE_OF_ARRAY] {0.0};
    
    // structs for timing data
    struct rusage before, after;
    
    const char* TAG = "Stopwatch";
    
    /**
     * Returns number of seconds between b and a.
     */
    double calculate();
    
public:

    // debug info
    void tagging(const char* NAME);

    // constructor for debug
    Stopwatch();
    
    // destructor  for debug
    ~Stopwatch();
    
    // get results for report them
    double getResults(int index);
    
    // start a stopwatch
    void start();
    
    // stop a stopwatch
    void stop();
    
    // determining the time difference
    int calculate(int index);
};

#endif // STOPWATCH_H