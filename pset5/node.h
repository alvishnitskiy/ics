// LinkedList creation

#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

#include <stdexcept>

class Node {

private:

    // data to save
    int data;
    
    // pointer to next node
    Node* next;
    
    const char* TAG = "node";

public:

    // debug info
    void tagging(const char* NAME);
    
    // constructor by default
    Node();
    
    // constructor with initialization of inner data
    Node(int info);
    
    // destructor for debug
    ~Node();
    
    // get inner data
    int getData();
    
    // assigned to inner data
    void setData(int info);
    
    // return next node
    Node* getNextNode();
    
    // assigned next node
    void setNextNode(Node* node);
};

#endif // NODE_H