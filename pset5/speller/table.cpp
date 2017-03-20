/**
 * Implements a hash table's functionality.
 */

#include <iostream>
using namespace std;

#include <stdexcept>

#include "table.h"

// debug info
void HashMap::tagging(const char* NAME) {
    cout<<TAG<<" === "<<NAME<<" === "<<endl;
}

// constructor with initialization by default
HashMap::HashMap() {
    //tagging("HashMap()");
    
    // 
    hashMap = new LinkedList[SIZE_ON_DEFAULT];
    sizeOfArray = SIZE_ON_DEFAULT;
    sizeOfMap = 0;
}

// constructor with initialization of inner array
HashMap::HashMap(int size) {
    //tagging("HashMap(int size)");
    
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
    //tagging("~HashMap()");
    
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
    //tagging("listIsEmpty");
    return list->isEmpty();
}

// add new node
bool HashMap::add(const char* word) {
    //tagging("add");
    
    // using hash function
    LinkedList* slider = &hashMap[hash(word)];
    slider->add(word);
    
    sizeOfMap++;
    return true;
}
    
// find the data
bool HashMap::find(const char* word) {
    //tagging("find");
    
    LinkedList* slider = &hashMap[hash(word)];
    
    if(slider->find(word)) {
        return true;
    }
    
    return false;
}

// remove all nodes from map
bool HashMap::removeAll() {
    //tagging("removeAll");
    
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
    //tagging("size");
    return sizeOfMap;
}

// show all data in map
void HashMap::show() {
    //tagging("show");
    
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
    //tagging("hash");
    
    const int POLYNOM = 37;
    unsigned int hashVal = 0;
    // The code computes a polynomial function (of 37) by use of Horner’s rule.

    for(int ch = 0, n = strlen(key); ch < n; ch++ ) {
        hashVal = POLYNOM * hashVal + ch;
    }
    return hashVal % sizeOfArray;
}