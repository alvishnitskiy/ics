/**
 * Implements a spell-checker.
 */

#include "speller.h"

#undef calculate
#undef getrusage

#include <iostream>
#include <iomanip>
using namespace std;

#define DEBUG

// default dictionary
#define DICTIONARY "dictionaries/large"

enum times {
    TIME_LOAD = 0, TIME_CHECK, TIME_SIZE, TIME_UNLOAD, TIME_TOTAL
};

#ifdef DEBUG
// debug info
void Speller::tagging(const char* NAME) {
    cout<<TAG<<" === "<<NAME<<" === "<<endl;
}
#endif

// constructor for debug
Speller::Speller() {
#ifdef DEBUG
    //tagging("Speller()");
#endif
};

// constructor with filenames
Speller::Speller(const char* dictName, char* textName) {
#ifdef DEBUG
    //tagging(TAG, "Speller(const char*, char*)");
#endif
    dictionary = dictName;
    text = textName;
};

// destructor  for debug
Speller::~Speller() {
#ifdef DEBUG
    //tagging("~Speller()");
#endif
};

// organization of resources to check words
int Speller::checking() {
#ifdef DEBUG
    //tagging(TAG, "checking");
#endif
    // class for measurement of time
    Stopwatch stopwatch;
    
    // class with template data structure
    Dictionary <Trie> dict;
    
    // load dictionary
    int res = loadDictionary(stopwatch, dict);
    if(res) {
        return res;
    }
    
    // try to open text
    FILE *fp = fopen(text, "rb");
    if (fp == NULL)
    {
        cout<<"Could not open "<<text<<"."<<endl;
        dict.unload();
        return 1;
    }
    
    // class for analyze words by letters
    WordsAudit* wordsAudit = new WordsAudit(stopwatch, dict, fp);
    
    // find words and report misspellings
    wordsAudit->findMisspellings();

    // check whether there was an error
    if (ferror(fp))
    {
        fclose(fp);
        cout<<"Error reading "<<text<<"."<<endl;
        dict.unload();
        return 1;
    }

    // close text
    fclose(fp);

    // determine dictionary's size
    unsigned int n = determineDictionarySize(stopwatch, dict);

    // unload dictionary
    res = unloaDictionary(stopwatch, dict);
    if(res) {
        return res;
    }
    
    // calculate total time
    stopwatch.calculate(TIME_TOTAL);

    // report benchmarks
    reportBenchmarks(stopwatch, wordsAudit->getMisspellings(), 
                             n, wordsAudit->getWords());

    // complete analysis
    delete wordsAudit;
    
    // that's all folks
    return 0;
}

// load dictionary
int Speller::loadDictionary(Stopwatch& stopwatch, Dictionary <Trie>& dict) {
#ifdef DEBUG
    //tagging(TAG, "loadDictionary");
#endif

    stopwatch.start();
    bool loaded = dict.load(dictionary);
    stopwatch.stop();

    // abort if dictionary not loaded
    if (!loaded)
    {
        cout<<"Could not load "<<dictionary<<"."<<endl;
        return 1;
    }

    // calculate time to load dictionary
    stopwatch.calculate(TIME_LOAD);
    
    return 0;
}

// determine dictionary's size
unsigned int Speller::determineDictionarySize(Stopwatch& stopwatch, Dictionary <Trie>& dict) {       
#ifdef DEBUG
    //tagging(TAG, "determineDictionarySize");
#endif

    stopwatch.start();
    unsigned int dictSize = dict.size();
    stopwatch.stop();

    // calculate time to determine dictionary's size
    stopwatch.calculate(TIME_SIZE);
    
    return dictSize;
}

// unload dictionary
int Speller::unloaDictionary(Stopwatch& stopwatch, Dictionary <Trie>& dict) { 
#ifdef DEBUG
    //tagging(TAG, "unloaDictionary");
#endif

    stopwatch.start();
    bool unloaded = dict.unload();
    stopwatch.stop();

    // abort if dictionary not unloaded
    if (!unloaded)
    {
        cout<<"Could not unload "<<dictionary<<"."<<endl;
        return 1;
    }

    // calculate time to unload dictionary
    stopwatch.calculate(TIME_UNLOAD);
    
    return 0;
}

// report benchmarks
void Speller::reportBenchmarks(Stopwatch& stopwatch, int misspellings, unsigned int& n, int words) {
#ifdef DEBUG
    //tagging(TAG, "reportBenchmarks");
#endif

    cout<<endl
        <<"WORDS MISSPELLED:     "<<misspellings<<endl
        <<"WORDS IN DICTIONARY:  "<<n<<endl
        <<"WORDS IN TEXT:        "<<words<<endl<<fixed<<setprecision( 2 )
        <<"TIME IN load:         "<<stopwatch.getResults(TIME_LOAD)<<endl
        <<"TIME IN check:        "<<stopwatch.getResults(TIME_CHECK)<<endl
        <<"TIME IN size:         "<<stopwatch.getResults(TIME_SIZE)<<endl
        <<"TIME IN unload:       "<<stopwatch.getResults(TIME_UNLOAD)<<endl
        <<"TIME IN TOTAL:        "<<stopwatch.getResults(TIME_TOTAL)<<endl<<endl;
}


int main(int argc, char *argv[])
{   
    // check for correct number of args
    if (argc != 2 && argc != 3)
    {
        cout<<"Usage: speller [dictionary] text"<<endl;
        return 1;
    }

    // determine dictionary to use
    const char* dictionary = (argc == 3) ? argv[1] : DICTIONARY;

    // try to open text
    char *text = (argc == 3) ? argv[2] : argv[1];

    // organization of spell-checking with definite dictionary and textfile
    Speller* speller = new Speller(dictionary, text);
    
    // organization of resources to check words
    speller->checking();

    // complete spell-checking
    delete speller;
    
    // that's all folks
    return 0;
}
