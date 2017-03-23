/**
 * Implements a hash table's functionality.
 */

#include <iostream>
using namespace std;

#include <stdexcept>

#include "table.h"

#define DEBUG

#ifdef DEBUG
// debug info
void HashMap::tagging(const char* NAME) {
    cout<<TAG<<" === "<<NAME<<" === "<<endl;
}
#endif

// constructor with initialization by default
HashMap::HashMap() {
#ifdef DEBUG
    //tagging("HashMap()");
#endif
    hashMap = new LinkedList[SIZE_ON_DEFAULT];
    sizeOfArray = SIZE_ON_DEFAULT;
    sizeOfMap = 0;
}

// constructor with initialization of inner array
HashMap::HashMap(int size) {
#ifdef DEBUG
    //tagging("HashMap(int size)");
#endif    
    // if incorrect
    if(size < 1) {
        // memory allocation in the range of positive integers
        throw (std::out_of_range("elements in memory less than 1"));
    }
    
    hashMap = new LinkedList[size];
    sizeOfArray = size;
    sizeOfMap = 0;
}

// cynical breaking inner data
HashMap::~HashMap() {
#ifdef DEBUG
    //tagging("~HashMap()");
#endif
    for(int i = 0; i < sizeOfArray; i++ ){
        LinkedList* slider = &hashMap[i];
        if(!listIsEmpty(slider)) {
            slider->removeAll();
        }
    }
    delete [] hashMap;
}

// if main node of list is empty
bool HashMap::listIsEmpty(LinkedList* list) {
#ifdef DEBUG
    //tagging("listIsEmpty");
#endif
    return list->isEmpty();
}

// add new node
bool HashMap::add(const char* word) {
#ifdef DEBUG
    //tagging("add");
#endif
    // using hash function
    LinkedList* slider = &hashMap[hash(word)];
    slider->add(word);
    
    sizeOfMap++;
    return true;
}
    
// find the data
bool HashMap::find(const char* word) {
#ifdef DEBUG
    //tagging("find");
#endif    
    LinkedList* slider = &hashMap[hash(word)];
    
    if(slider->find(word)) {
        return true;
    }
    
    return false;
}

// remove all nodes from map
bool HashMap::removeAll() {
#ifdef DEBUG
    //tagging("removeAll");
#endif
    for(int i = 0; i < sizeOfArray; i++ ){
        LinkedList* slider = &hashMap[i];
        if(!listIsEmpty(slider)){
            if(!slider->removeAll()){
                return false;
            }
        }
    }
    return true;
}

// get number of data in map
unsigned int HashMap::size() {
#ifdef DEBUG
    //tagging("size");
#endif
    return sizeOfMap;
}

// show all data in map
void HashMap::show() {
#ifdef DEBUG
    //tagging("show");
#endif
    for(int i = 0; i < sizeOfArray; i++) {
        hashMap[i].show();
    }
    cout<<endl;
}

/**
 * A hash routine for string objects.
 * The source of information: 
 * Weiss, Mark Allen.
 *    Data structures and algorithm analysis in C++ / Mark Allen Weiss, Florida International University
 */
int HashMap::hash(const char* key) {
#ifdef DEBUG
    //tagging("hash");
#endif

    const int POLYNOM = 37;
    unsigned int hashVal = 0;
    // The code computes a polynomial function (of 37) by use of Horner’s rule.

    for(int ch = 0, n = strlen(key); ch < n; ch++ ) {
        hashVal = POLYNOM * hashVal + ch;
    }
    return hashVal % sizeOfArray;
}