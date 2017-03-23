/**
 * Declares a hash table's functionality.
 */

#ifndef TABLE_H
#define TABLE_H

#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

#include "list.h"

//#define SIZE 50

class HashMap {

private:
    
    // default size of hashMap in memory
    const int SIZE_ON_DEFAULT = 50;
    
    // pointer to begin of base array
    LinkedList* hashMap;
    
    // number of data in map
    unsigned int sizeOfMap;
    
    // size of base array
    int sizeOfArray;
    
    const char* TAG = "hash_map";
    
public:
    
    // debug info
    void tagging(const char* NAME);
    
    // constructor with initialization by default
    HashMap();

    // constructor with initialization of inner array
    HashMap(int size);
    
    // cynical breaking inner data
    ~HashMap();
    
    // if main node of list is empty
    bool listIsEmpty(LinkedList* list);
    
    // add new node
    bool add(const char* word);
    
    // find the data
    bool find(const char* word);
    
    // remove all nodes from map
    bool removeAll();
    
    // get number of data in map
    unsigned int size();

    // show all data in map
    void show();
    
    // using hash function
    int hash(const char* key);
};

#endif // TABLE_H
