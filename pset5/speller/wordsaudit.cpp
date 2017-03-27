/**
 * Implements analyzer words by letters.
 */

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "stopwatch.h"
#include "wordsaudit.h"
#include "dictionary.h"

#include <iostream>
#include <iomanip>
using namespace std;

#define DEBUG

enum times {
    TIME_LOAD = 0, TIME_CHECK, TIME_SIZE, TIME_UNLOAD, TIME_TOTAL
};

#ifdef DEBUG
// debug info
void WordsAudit::tagging(const char* NAME) {
    cout<<TAG<<" === "<<NAME<<" === "<<endl;
}
#endif

// constructor for debug
WordsAudit::WordsAudit() {
#ifdef DEBUG
    //tagging("WordsAudit()");
#endif
};

// constructor with using stopwatch, default datastructure and textfile
WordsAudit::WordsAudit(Stopwatch& stopwatc, Dictionary <Trie>& dictionary, FILE* filePointer) {
#ifdef DEBUG
    //tagging(TAG, "WordsAudit(FILE* fp)");
#endif
    stopwatch = &stopwatc;
    dict = &dictionary;
    fp = filePointer;
};

// destructor  for debug
WordsAudit::~WordsAudit() {
#ifdef DEBUG
    //tagging("~WordsAudit()");
#endif
};

// find words and report misspellings
void WordsAudit::findMisspellings() {
#ifdef DEBUG    
    //tagging(TAG, "findMisspellings");
#endif
    // prepare to report misspellings
    cout<<endl<<"MISSPELLED WORDS"<<endl<<endl;

    // spell-check each word in text
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        // allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // alphabetical characters and apostrophes
            alphabetApostrophe(c, fp);
        }

        // ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // consume remainder of alphanumeric string
            while ((c = fgetc(fp)) != EOF && isalnum(c));

            // prepare for new word
            index = 0;
        }

        // we must have found a whole word
        else if (index > 0)
        {
            // find a whole word
            findWholeWord(*stopwatch, *dict);
        }
    }
}

// alphabetical characters and apostrophes
void WordsAudit::alphabetApostrophe(int& c, FILE* fp) {
#ifdef DEBUG
    //tagging(TAG, "alphabetApostrophe");
#endif
    // append character to word
    word[index] = c;
    index++;

    // ignore alphabetical strings too long to be words
    if (index > LENGTH)
    {
        // consume remainder of alphabetical string
        while ((c = fgetc(fp)) != EOF && isalpha(c));

        // prepare for new word
        index = 0;
    }
}

// find a whole word and report misspellings
void WordsAudit::findWholeWord(Stopwatch& stopwatch, Dictionary <Trie>& dict) {
#ifdef DEBUG
    //tagging(TAG, "foundWholeWord");
#endif
    // terminate current word
    word[index] = '\0';

    // update counter
    words++;

    // check word's spelling
    stopwatch.start();
    bool misspelled = !dict.check(word);
    stopwatch.stop();

    // update benchmark
    stopwatch.calculate(TIME_CHECK);

    // print word if misspelled
    if (misspelled)
    {
        cout<<word<<endl;
        misspellings++;
    }

    // prepare for next word
    index = 0;
}

// get number of misspellings for report
int WordsAudit::getMisspellings() {
#ifdef DEBUG
    //tagging(TAG, "getMisspellings");
#endif
    return misspellings;
}

// get number of words in text for report
int WordsAudit::getWords() {
#ifdef DEBUG
    //tagging(TAG, "getWords");
#endif
    return words;
}
