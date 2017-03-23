/**
 * Implements a linked list's functionality.
 */

#include <iostream>
using namespace std;

#include <stdexcept>

#include "list.h"

#define DEBUG

#ifdef DEBUG
// debug info
void Node::tagging(const char* NAME) {
    cout<<TAG<<" === "<<NAME<<" === "<<endl;
}
#endif

// constructor by default
Node::Node(){
#ifdef DEBUG
    //tagging("Node()");
#endif
    this->next = NULL;
};

// constructor with initialization of inner data
Node::Node(const char* word) {
#ifdef DEBUG
    //tagging("Node(int info)");
#endif
    strcpy(this->word, word);
    this->next = NULL;
};

// destructor for debug
Node::~Node(){
#ifdef DEBUG
    //tagging("~Node()");
#endif
};

// get inner data
const char* Node::getData() {
#ifdef DEBUG
    //tagging("getData");
#endif

    return this->word;
}

// assigned to inner data
void Node::setData(const char* word) {
#ifdef DEBUG
    //tagging("setData");
#endif

    strcpy(this->word, word);
}

// return next node
Node* Node::getNextNode() {
#ifdef DEBUG
    //tagging("getNextNode");
#endif

    return this->next;
}

// assigned next node
void Node::setNextNode(Node* node) {
#ifdef DEBUG
    //tagging("setNextNode");
#endif

    this->next = node;
}

//==============================================================

#ifdef DEBUG
// debug info
void LinkedList::tagging(const char* NAME) {
    cout<<TAG<<" === "<<NAME<<" === "<<endl;
}
#endif

// constructor with zero initialization
LinkedList::LinkedList() {
#ifdef DEBUG
    //tagging("LinkedList()");
#endif
    head = NULL;
    sizeOfList = 0;
}

// cynical breaking inner data
LinkedList::~LinkedList() {
#ifdef DEBUG
    //tagging("~LinkedList()");
#endif
    // freeing nodes using temporary node
    while (head != NULL) {
        Node* temp = head;
        head = head->getNextNode();
        delete temp;
    }
}

// if main node is empty
bool LinkedList::isEmpty() {
#ifdef DEBUG
    //tagging("isEmpty");
#endif

    return NULL == head;
}

// add new node
bool LinkedList::add(const char* word) {
#ifdef DEBUG
    //tagging("add");
#endif

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
#ifdef DEBUG
    //tagging("get");
#endif
    // if incorrect
    if(index < 0 || index > sizeOfList - 1){
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
#ifdef DEBUG
    //tagging("find");
#endif

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
#ifdef DEBUG
    //tagging("remove");
#endif

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
#ifdef DEBUG
    //tagging("removeAll");
#endif

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
#ifdef DEBUG
    //tagging("size");
#endif

    return sizeOfList;
}

// show all data in list
void LinkedList::show() {
#ifdef DEBUG
    //tagging("show");
#endif
    
    if(!isEmpty()) {
        Node* cursor = head;
        
        for(int i = 0; i < sizeOfList; i++) {
            cout<<cursor->getData()<<" ";
            cursor = cursor->getNextNode();
        }
    }
    cout<<endl;
}