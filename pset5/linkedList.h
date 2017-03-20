// LinkedList creation

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

#include <stdexcept>

#include "node.h"

class LinkedList {

private:
    
    // pointer to main node
    Node* head;
    
    // number of data in list
    int sizeOfList;
    
    const char* TAG = "linked_list";
    
public:

    // debug info
    void tagging(const char* NAME);
    
    // constructor with zero initialization
    LinkedList();

    // cynical breaking inner data
    ~LinkedList();
    
    // if main node is empty
    bool isEmpty();
    
    // add new node
    bool add(int info);
    
    // get data by index
    int get(int index);
    
    // find the data
    bool find(int info);
    
    // remove node
    bool remove();

    // remove all nodes from list
    bool removeAll();
    
    // get number of data in list
    int size();

    // show all data in list
    void show();
};

#endif // LINKEDLIST_H