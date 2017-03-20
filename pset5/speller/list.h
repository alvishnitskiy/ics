/**
 * Declares a linked list's functionality.
 */

#ifndef LIST_H
#define LIST_H

#include <strings.h>

#include "dictionary.h"

class Node {

private:

    // data to save
    char word[LENGTH + 1];
    
    // pointer to next node
    Node* next;
    
    const char* TAG = "node";

public:

    // debug info
    void tagging(const char* NAME);
    
    // constructor by default
    Node();
    
    // constructor with initialization of inner data
    Node(const char* word);
    
    // destructor for debug
    ~Node();
    
    // get inner data
    const char* getData();
    
    // assigned to inner data
    void setData(const char* word);
    
    // return next node
    Node* getNextNode();
    
    // assigned next node
    void setNextNode(Node* node);
};

class LinkedList {

private:
    
    // pointer to main node
    Node* head;
    
    // number of data in list
    unsigned int sizeOfList;
    
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
    bool add(const char* word);
    
    // get data by index
    const char* get(int index);
    
    // find the data
    bool find(const char* word);
    
    // remove node
    bool remove();

    // remove all nodes from list
    bool removeAll();
    
    // get number of data in list
    unsigned int size();

    // show all data in list
    void show();
};

#endif // LIST_H
