// LinkedList creation

#include <iostream>
using namespace std;

#include <stdexcept>

#include "node.h"
#include "linkedList.h"
#include "hashMap.h"

//#define DEBUG

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
    data = 0;
    this->next = NULL;
};

// constructor with initialization of inner data
Node::Node(int info) {
#ifdef DEBUG
    //tagging("Node(int info)");
#endif
    this->data = info;
    this->next = NULL;
};

// destructor for debug
Node::~Node(){
#ifdef DEBUG
    //tagging("~Node()");
#endif
};

// get inner data
int Node::getData() {
#ifdef DEBUG
    //tagging("getData");
#endif
    return this->data;
}

// assigned to inner data
void Node::setData(int info) {
#ifdef DEBUG
    //tagging("setData");
#endif
    this->data = info;
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

// add to the end of list
bool LinkedList::addNext(Node* cursor, Node* newNode) {
#ifdef DEBUG
    //tagging("addNext");
#endif

    if (NULL == cursor){
        head = newNode;
        sizeOfList++;
        return true;
    }
    
    if(NULL == cursor->getNextNode()) {
        // reached the end of list
        cursor->setNextNode(newNode);
        sizeOfList++;
        return true;
    }
    
    return addNext(cursor->getNextNode(), newNode);
}

// get next data by index
int LinkedList::getNextData(Node* cursor, int counter) {
#ifdef DEBUG
    //tagging("getNextData");
#endif
    
    if(counter > 0) {
        return getNextData(cursor->getNextNode(), --counter);
    }
    
    return cursor->getData();
}

// recursively find the next node
bool LinkedList::findNext(Node* cursor, int& info) {
#ifdef DEBUG
    //tagging("findNext");
#endif

    if(NULL == cursor) {
        return false;
    }
    
    if(cursor->getData() == info) {
        return true;
    }
        
    return findNext(cursor->getNextNode(), info);
}

// recursively delete the next node
bool LinkedList::removeNext(Node* previous, Node* current, int counter) {
#ifdef DEBUG
    //tagging("removeNext");
#endif

    if(NULL == current) {
        return false;
    }
    
    if(counter > 0) {
        return removeNext(current, current->getNextNode(), --counter);
    }

    if(current == head) {
        head = head->getNextNode();
    }
    else {
        previous->setNextNode(current->getNextNode());
    }
    delete current;
    sizeOfList--;
    return true;
}

// show data in next node
void LinkedList::showNext(Node* cursor) {
#ifdef DEBUG
    //tagging("showNext");
#endif

    if(cursor != NULL)  {
        cout<<cursor->getData()<<" ";
        showNext(cursor->getNextNode());
    }
}

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
};

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
};

// if main node is empty
bool LinkedList::isEmpty() {
#ifdef DEBUG
    //tagging("isEmpty");
#endif
    return NULL == head;
}

// add new node
bool LinkedList::add(int info) {
#ifdef DEBUG
    //tagging("add");
#endif

    Node* newNode = new Node;
    if (NULL == newNode){
        return false;
    }
    newNode->setData(info);
    
    return addNext(head, newNode);
}

// get data by index
int LinkedList::get(int index) {
#ifdef DEBUG
    //tagging("get");
#endif
    // if incorrect
    if(index < 0 || index > sizeOfList - 1){
        throw (std::invalid_argument("bad argument"));
    }
    
    return getNextData(head, index);
}

// find the data
bool LinkedList::find(int info) {
#ifdef DEBUG
    //tagging("find");
#endif

    if(isEmpty()) {
        return false;
    }
    return findNext(head, info);
}

// remove node by index
bool LinkedList::remove(int index) {
#ifdef DEBUG
    //tagging("remove");
#endif

    // if incorrect
    if(index < 0 || index > sizeOfList - 1){
        throw (std::invalid_argument("bad argument"));
    }

    return removeNext(head, head, index);
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
int LinkedList::size() {
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
        showNext(head);
    }
    cout<<endl;
}

//==============================================================

// get next data by index in list
int HashMap::getNextData(int arrayPosition, int counter) {
#ifdef DEBUG
    tagging("getNextData");
#endif

    if(!listIsEmpty(&hashMap[arrayPosition])){
        // is counter in this list ?
        int localSize = (&hashMap[arrayPosition])->size();
        if(counter - localSize >= 0){
            return getNextData(++arrayPosition, counter - localSize);
        }
        else {
            return (&hashMap[arrayPosition])->get(counter);
        }
    }
    // if list is empty
    return getNextData(++arrayPosition, counter);
}

// recursively delete the next node in list
bool HashMap::removeNext(int arrayPosition, int counter) {
#ifdef DEBUG
    tagging("removeNext");
#endif

    if(!listIsEmpty(&hashMap[arrayPosition])){
        // is counter in this list ?
        int localSize = (&hashMap[arrayPosition])->size();
        if(counter - localSize >= 0){
            return removeNext(++arrayPosition, counter - localSize);
        }
        else {
            bool result = (&hashMap[arrayPosition])->remove(counter);
            if(result) {
                sizeOfMap--;
            }
            return result;
        }
    }
    // if list is empty
    return removeNext(++arrayPosition, counter);
}

// show data in next list
void HashMap::showNext(int arrayPosition) {
#ifdef DEBUG
    tagging("showNext");
#endif

    if (arrayPosition < sizeOfArray) {
        if(!listIsEmpty(&hashMap[arrayPosition])){
            hashMap[arrayPosition].show();
        }
        // if list is empty
        showNext(++arrayPosition);
    }
}

#ifdef DEBUG
// debug info
void HashMap::tagging(const char* NAME) {
    cout<<TAG<<" === "<<NAME<<" === "<<endl;
}
#endif

// constructor with initialization by default
HashMap::HashMap() {
#ifdef DEBUG
    tagging("HashMap()");
#endif
    hashMap = new LinkedList[SIZE_ON_DEFAULT];
    sizeOfArray = SIZE_ON_DEFAULT;
    sizeOfMap = 0;
};

// constructor with initialization of inner array
HashMap::HashMap(int size) {
#ifdef DEBUG
    tagging("HashMap(int size)");
#endif

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
#ifdef DEBUG
    tagging("~HashMap()");
#endif

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
#ifdef DEBUG
    tagging("listIsEmpty");
#endif
    return list->isEmpty();
}

// add new node
bool HashMap::add(int info) {
#ifdef DEBUG
    tagging("add");
#endif
    // using hash function
    LinkedList* slider = &hashMap[hashFunc(info)];
    slider->add(info);
    
    sizeOfMap++;
    return true;
}

// get data by index
int HashMap::get(int index) {
#ifdef DEBUG
    tagging("get");
#endif

    // if incorrect
    if(index < 0 || index > sizeOfMap - 1){
        throw (std::invalid_argument("bad argument"));
    }
    
    // get next data by index in list
    return getNextData(0, index);
}

// find the data
bool HashMap::find(int info) {
#ifdef DEBUG
    tagging("find");
#endif

    LinkedList* slider = &hashMap[hashFunc(info)];
    
    if(!listIsEmpty(slider)) {
        
        if(slider->find(info)) {
            return true;
        }
    }
    return false;
}

// remove node by index
bool HashMap::remove(int index) {
#ifdef DEBUG
    tagging("remove");
#endif

    // if incorrect
    if(index < 0 || index > sizeOfMap - 1){
        throw (std::invalid_argument("bad argument"));
    }
    
    // recursively delete the next node in list
    return removeNext(0, index);
}

// remove all nodes from map
bool HashMap::removeAll() {
#ifdef DEBUG
    tagging("removeAll");
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
int HashMap::size() {
#ifdef DEBUG
    tagging("size");
#endif
    return sizeOfMap;
}

// show all data in map
void HashMap::show() {
#ifdef DEBUG
    tagging("show");
#endif

    showNext(0);
}

/**
 * A hash routine for string objects (in this case - integers).
 * The source of information: 
 * Weiss, Mark Allen.
 *    Data structures and algorithm analysis in C++ / Mark Allen Weiss, Florida International University
 */
int HashMap::hashFunc(int info) {
#ifdef DEBUG
    tagging("hash");
#endif

    const int POLYNOM = 37;
    unsigned int hashVal = 0;
    // The code computes a polynomial function (of 37) by use of Horner’s rule.

    for(int i = 0; i < info; i++ ) {
        hashVal = POLYNOM * hashVal + i;
    }
    return hashVal % sizeOfArray;
}

//==============================================================

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
    cout<<lklist->remove(10)<<endl;
    for(int i = 0; i < 20; i++) {
        cout<<i<<" "
            <<lklist->remove(i)<<endl;
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
    cout<<hm->get(6)<<endl;
    cout<<hm->remove(0)<<endl;
    hm->show();
    for(int i = 10; i >= 0; i--) {
        cout<<i<<" "
            <<hm->remove(i)<<endl;
    }
    hm->show();
    delete hm;
       
    return 0;
}