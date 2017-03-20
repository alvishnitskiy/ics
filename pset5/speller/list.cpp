/**
 * Implements a linked list's functionality.
 */

#include <iostream>
using namespace std;

#include <stdexcept>

#include "list.h"

// debug info
void Node::tagging(const char* NAME) {
    cout<<TAG<<" === "<<NAME<<" === "<<endl;
}

// constructor by default
Node::Node(){
    //tagging("Node()");
    this->next = NULL;
};

// constructor with initialization of inner data
Node::Node(const char* word) {
    //tagging("Node(int info)");
    strcpy(this->word, word);
    this->next = NULL;
};

// destructor for debug
Node::~Node(){
    //tagging("~Node()");
};

// get inner data
const char* Node::getData() {
    //tagging("getData");
    return this->word;
}

// assigned to inner data
void Node::setData(const char* word) {
    //tagging("setData");
    strcpy(this->word, word);
}

// return next node
Node* Node::getNextNode() {
    //tagging("getNextNode");
    return this->next;
}

// assigned next node
void Node::setNextNode(Node* node) {
    //tagging("setNextNode");
    this->next = node;
}

//==============================================================

// debug info
void LinkedList::tagging(const char* NAME) {
    cout<<TAG<<" === "<<NAME<<" === "<<endl;
}

// constructor with zero initialization
LinkedList::LinkedList() {
    //tagging("LinkedList()");
    
    //
    head = NULL;
    sizeOfList = 0;
}

// cynical breaking inner data
LinkedList::~LinkedList() {
    //tagging("~LinkedList()");
    
    // freeing nodes using temporary node
    while (head != NULL) {
        Node* temp = head;
        head = head->getNextNode();
        delete temp;
    }
}

// if main node is empty
bool LinkedList::isEmpty() {
    //tagging("isEmpty");
    return NULL == head;
}

// add new node
bool LinkedList::add(const char* word) {
    //tagging("add");
    
    Node* newNode = new Node;
    if (NULL == newNode){
        return false;
    }
    newNode->setData(word);
    
    if(isEmpty()) {
        head = newNode;
    }
    else {
        // new node as agent
        newNode->setNextNode(head);
        head = newNode;
    }
    sizeOfList++;
    return true;
}

// get data by index
const char* LinkedList::get(int index) {
    //tagging("get");
    
    // if incorrect
    if(index < 0 || index > sizeOfList){
        throw (std::invalid_argument("bad argument"));
    }
    
    Node* cursor = head;
    
    for(int i = 0; i < index; i++) {
        cursor = cursor->getNextNode();
    }
    
    return cursor->getData();
}

// find the data
bool LinkedList::find(const char* word) {
    //tagging("find");
    
    if(isEmpty()) {
        return false;
    }
    Node* cursor = head;
    
    while (cursor != NULL) {
        if(!strcasecmp(cursor->getData(), word)) {
            return true;
        }
        cursor = cursor->getNextNode();
    }
    
    return false;
}

// remove node
bool LinkedList::remove() {
    //tagging("remove");
    
    if(isEmpty()) {
        return false;
    }
    Node* temp = head;
    head = head->getNextNode();
    delete temp;
    
    sizeOfList--;
    return true;
}

// remove all nodes from list
bool LinkedList::removeAll() {
    //tagging("removeAll");
    
    while(!isEmpty()) {
        // freeing nodes using temporary node
        Node* temp = head;
        head = head->getNextNode();
        delete temp;
    }
    if(isEmpty()) {
        return true;
    }
    return false;
}

// get number of data in list
unsigned int LinkedList::size() {
    //tagging("size");
    return sizeOfList;
}

// show all data in list
void LinkedList::show() {
    //tagging("show");
    
    if(!isEmpty()) {
        Node* cursor = head;
        
        for(int i = 0; i < sizeOfList; i++) {
            cout<<cursor->getData()<<" ";
            cursor = cursor->getNextNode();
        }
    }
    cout<<endl;
}