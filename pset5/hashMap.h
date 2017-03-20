// LinkedList creation

#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
using namespace std;

#include <stdexcept>

#include "linkedList.h"

class HashMap {

private:
    
    // default size of hashMap in memory
    const int SIZE_ON_DEFAULT = 10;
    
    // pointer to begin of base array
    LinkedList* hashMap;
    
    // number of data in map
    int sizeOfMap;
    
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
    bool add(int info);
    
    // find the data
    bool find(int info);

    // remove all nodes from map
    bool removeAll();
    
    // get number of data in map
    int size();

    // show all data in map
    void show();
    
    // using hash function
    int hashFunc(int info);
};

#endif // HASHMAP_H