/**
 * Declares a spell-checker.
 */

#ifndef SPELLER_H
#define SPELLER_H

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "stopwatch.h"
#include "wordsaudit.h"
#include "dictionary.h"
#include "table.h"

class Speller {

private:

    // name of dictionary file
    const char* dictionary;

    // name of using textfile
    char* text;
    
    const char* TAG = "Speller";
    
public:

    // debug info
    void tagging(const char* NAME);
    
    // constructor with filenames for dictionary and text
    Speller(const char* dictName, char* textName);
    
    // organization of resources to check words
    int checking();
    
    // load dictionary
    int loadDictionary(Stopwatch& stopwatch, Dictionary <HashMap>& dict);
    
    // determine dictionary's size
    unsigned int determineDictionarySize(Stopwatch& stopwatch, Dictionary <HashMap>& dict);
    
    // unload dictionary
    int unloaDictionary(Stopwatch& stopwatch, Dictionary <HashMap>& dict);
    
    // report benchmarks
    void reportBenchmarks(Stopwatch& stopwatch, int misspellings, unsigned int& n, int words);
};

#endif // SPELLER_H