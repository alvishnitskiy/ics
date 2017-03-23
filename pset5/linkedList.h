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
    
    // add to the end of list
    bool addNext(Node* cursor, Node* newNode);
    
    // get next data by index
    int getNextData(Node* cursor, int counter);
    
    // recursively find the next node
    bool findNext(Node* cursor, int& info);
    
    // recursively delete the next node
    bool removeNext(Node* previous, Node* current, int counter);
    
    // show data in next node
    void showNext(Node* cursor);
    
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
    
    // remove node by index
    bool remove(int index);

    // remove all nodes from list
    bool removeAll();
    
    // get number of data in list
    int size();

    // show all data in list
    void show();
};

#endif // LINKEDLIST_H