/**
 * Declares and implements in template a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

template <class DataStruct> class Dictionary {

public:

    // default datastructure
    DataStruct* dataStruct;
    
    // constructor with using datastructure
    Dictionary <DataStruct>() {
        dataStruct = new DataStruct;
    };
    
    // destructor for breaking data structure
    ~Dictionary <DataStruct>() {
        delete dataStruct;
    };

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

};

/**
 * Returns true if word is in dictionary else false.
 */
template <class DataStruct>
bool Dictionary <DataStruct>::check(const char* word)
{
    // find the word in default datastructure
    return dataStruct->find(word);
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
template <class DataStruct>
bool Dictionary <DataStruct>::load(const char* dictionary)
{
    // open dictionary file
    FILE *dictptr = fopen(dictionary, "r");
    if (dictptr == NULL){
        cout<<"Could not open "<<dictionary<<"."<<endl;
        return false;
    }
    
    // create temporary word
    char tmp_word[LENGTH + 1];
    
    int position = 0;
    // until the end of file
    while ((position = fscanf(dictptr, "%s", tmp_word)) != EOF) {

        // add each word to datastructure
        if (!dataStruct->add(tmp_word)){
            return false;
        }
    }
    
    if(position == EOF) {
        // close dictionary file
        fclose(dictptr);
        
        return true;
    }
    
    // close dictionary file
    fclose(dictptr);
    
    // not loaded
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
template <class DataStruct>
unsigned int Dictionary <DataStruct>::size(void)
{
    // get number of words in datastructure
    return dataStruct->size();
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
template <class DataStruct>
bool Dictionary <DataStruct>::unload(void)
{
    // clean datastructure
    if(dataStruct->removeAll()) {
        //delete dataStruct;
        return true;
    }
    return false;
}

#endif // DICTIONARY_H
