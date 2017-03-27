/**
 * Declares analyzer words by letters.
 */

#ifndef WORDSAUDIT_H
#define WORDSAUDIT_H

#include "stopwatch.h"
#include "dictionary.h"
#include "trie.h"

class WordsAudit {

private:
    
    // pointer on using stopwatch
    Stopwatch* stopwatch;
    
    // pointer on default datastructure
    Dictionary <Trie>* dict;
    
    // pointer on textfile
    FILE* fp;
    
    // prepare to spell-check
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];
    
    const char* TAG = "WordsAudit";

public:
    
    // debug info
    void tagging(const char* NAME);
    
    // constructor for debug
    WordsAudit();
    
    // constructor with using stopwatch, default datastructure and textfile
    WordsAudit(Stopwatch& stopwatc, Dictionary <Trie>& dictionary, FILE* filePointer);
    
    // destructor  for debug
    ~WordsAudit();
    
    // find words and report misspellings
    void findMisspellings();
    
    // alphabetical characters and apostrophes
    void alphabetApostrophe(int& c, FILE* fp);

    // find a whole word and report misspellings
    void findWholeWord(Stopwatch& stopwatch, Dictionary <Trie>& dict);
    
    // get number of misspellings for report
    int getMisspellings();
    
    // get number of words in text for report
    int getWords();
};

#endif // WORDSAUDIT_H