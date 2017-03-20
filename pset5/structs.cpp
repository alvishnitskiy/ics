// LinkedList creation

#include <iostream>
using namespace std;

#include <stdexcept>

#include "node.h"
#include "linkedList.h"
#include "hashMap.h"

// debug info
void Node::tagging(const char* NAME) {
    cout<<TAG<<" === "<<NAME<<" === "<<endl;
}

// constructor by default
Node::Node(){
    //tagging("Node()");
    data = 0;
    this->next = NULL;
};

// constructor with initialization of inner data
Node::Node(int info) {
    //tagging("Node(int info)");
    this->data = info;
    this->next = NULL;
};

// destructor for debug
Node::~Node(){
    //tagging("~Node()");
};

// get inner data
int Node::getData() {
    //tagging("getData");
    return this->data;
}

// assigned to inner data
void Node::setData(int info) {
    //tagging("setData");
    this->data = info;
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
    tagging("LinkedList()");
    
    head = NULL;
    sizeOfList = 0;
};

// cynical breaking inner data
LinkedList::~LinkedList() {
    tagging("~LinkedList()");
    
    // freeing nodes using temporary node
    while (head != NULL) {
        Node* temp = head;
        head = head->getNextNode();
        delete temp;
    }
};

//
bool LinkedList::isEmpty() {
    tagging("isEmpty");
    return NULL == head;
}

// add new node
bool LinkedList::add(int info) {
    tagging("add");
    
    Node* newNode = new Node;
    if (NULL == newNode){
        return false;
    }
    newNode->setData(info);
    
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
int LinkedList::get(int index) {
    tagging("get");
    
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
bool LinkedList::find(int info) {
    tagging("find");
    
    if(isEmpty()) {
        return false;
    }
    Node* cursor = head;
    
    while (cursor != NULL) {
        if(cursor->getData() == info) {
            return true;
        }
        cursor = cursor->getNextNode();
    }
    
    return false;
}

// remove node
bool LinkedList::remove() {
    tagging("remove");
    
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
    tagging("removeAll");
    
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
int LinkedList::size() {
    tagging("size");
    return sizeOfList;
}

// show all data in list
void LinkedList::show() {
    tagging("show");
    
    if(!isEmpty()) {
        Node* cursor = head;
        
        for(int i = 0; i < sizeOfList; i++) {
            cout<<cursor->getData()<<" ";
            cursor = cursor->getNextNode();
        }
    }
    cout<<endl;
}

//==============================================================

// debug info
void HashMap::tagging(const char* NAME) {
    cout<<TAG<<" === "<<NAME<<" === "<<endl;
}

// constructor with initialization by default
HashMap::HashMap() {
    tagging("HashMap()");
    
    // 
    hashMap = new LinkedList[SIZE_ON_DEFAULT];
    sizeOfArray = SIZE_ON_DEFAULT;
    sizeOfMap = 0;
};

// constructor with initialization of inner array
HashMap::HashMap(int size) {
    tagging("HashMap(int size)");
    
    if(size < 1) {
        // memory allocation in the range of positive integers
        throw (std::out_of_range("elements in memory less than 1"));
    }
    
    hashMap = new LinkedList[size];
    sizeOfArray = size;
    sizeOfMap = 0;
};

// cynical breaking inner data
HashMap::~HashMap() {
    tagging("~HashMap()");
    
    for(int i = 0; i < sizeOfArray; i++ ){
        LinkedList* slider = &hashMap[i];
        if(!listIsEmpty(slider)) {
            slider->removeAll();
        }
    }
    delete [] hashMap;
};

// if main node of list is empty
bool HashMap::listIsEmpty(LinkedList* list) {
    tagging("listIsEmpty");
    return list->isEmpty();
}

// add new node
bool HashMap::add(int info) {
    tagging("add");
    
    // using hash function
    LinkedList* slider = &hashMap[hashFunc(info)];
    slider->add(info);
    
    sizeOfMap++;
    return true;
}

// find the data
bool HashMap::find(int info) {
    tagging("find");
    
    LinkedList* slider = &hashMap[hashFunc(info)];
    
    if(!listIsEmpty(slider)) {
        
        if(slider->find(info)) {
            return true;
        }
    }
    return false;
}

// remove all nodes from map
bool HashMap::removeAll() {
    tagging("removeAll");
    
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
int HashMap::size() {
    tagging("size");
    return sizeOfMap;
}

// show all data in map
void HashMap::show() {
    tagging("show");
    
    for(int i = 0; i < sizeOfArray; i++) {
        if(!listIsEmpty(&hashMap[i])){
            hashMap[i].show();
        }
    }
    cout<<endl;
}

/**
 * A hash routine for string objects (in this case - integers).
 * The source of information: 
 * Weiss, Mark Allen.
 *    Data structures and algorithm analysis in C++ / Mark Allen Weiss, Florida International University
 */
int HashMap::hashFunc(int info) {
    tagging("hash");
    
    const int POLYNOM = 37;
    unsigned int hashVal = 0;
    // The code computes a polynomial function (of 37) by use of Horner’s rule.

    for(int i = 0; i < info; i++ ) {
        hashVal = POLYNOM * hashVal + i;
    }
    return hashVal % sizeOfArray;
}

int main(void)
{
    /*Node* nd1 = new Node;
    nd1->setData(1);
    cout<<nd1->getData()<<endl;
    
    Node* nd2 = new Node(2);
    nd2->setNextNode(nd1);
    cout<<nd2->getData()<<endl;
    
    Node* tmp = nd2->getNextNode();
    cout<<tmp->getData()<<endl;
        
    delete nd1;
    delete nd2;*/
    
//======================================    
    
    /*LinkedList* lklist = new LinkedList();
    for(int i = 0; i < 15; i++) {
        lklist->add(i);
    }
    cout<<lklist->size()<<endl;
    lklist->show();
    cout<<lklist->get(5)<<endl;
    for(int i = 0; i < 20; i++) {
        cout<<lklist->remove()<<endl;
    }
    lklist->show();
    cout<<lklist->find(3)<<endl;
    lklist->show();
    //cout<<lklist->get(10)<<endl;
    //cout<<lklist->get(100)<<endl;
    delete lklist;*/
    
//======================================
    
    HashMap* hm = new HashMap();
    for(int i = 0; i < 15; i++) {
        hm->add(i);
    }
    cout<<hm->size()<<endl;
    cout<<hm->find(3)<<endl;
    hm->show();
    delete hm;
       
    return 0;
}