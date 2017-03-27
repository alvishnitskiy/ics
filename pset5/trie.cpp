/**
 * Implements a trie's functionality.
 */

#include "trie.h"

#include <iostream>
using namespace std;

#include <stdexcept>

//#define DEBUG

#ifdef DEBUG
// debug info
void NodeTrie::tagging(const char* NAME) {
    cout<<TAG<<" === "<<NAME<<" === "<<endl;
}
#endif

// clean start settings
NodeTrie::NodeTrie(){
#ifdef DEBUG
    //tagging("NodeTrie()");
#endif
    this->is_year = false;
    // free child references
    for(int j = 0; j < DECIMAL; j++ ){
        this->children[j] = NULL;
    }
};

// destructor for debug
NodeTrie::~NodeTrie(){
#ifdef DEBUG
    //tagging("~NodeTrie()");
#endif
};

// if child node is empty
bool NodeTrie::isEmptyChildNode(int index) {
#ifdef DEBUG
    //tagging("isEmpty");
#endif
    return NULL == this->children[index];
}

// get inner data
int NodeTrie::getData() {
#ifdef DEBUG
    //tagging("getData");
#endif
    return this->is_year;
}

// assigned to inner data
void NodeTrie::setData(bool year) {
#ifdef DEBUG
    //tagging("setData");
#endif
    this->is_year = year;
}

// return child node
NodeTrie* NodeTrie::getChildNode(int index) {
#ifdef DEBUG
    //tagging("getChildNode");
#endif
    return this->children[index];
}

// assigned child node
void NodeTrie::setChildNode(NodeTrie* node, int index) {
#ifdef DEBUG
    //tagging("setChildNode");
#endif
    this->children[index] = node;
}

//==============================================================

#ifdef DEBUG
// debug info
void Trie::tagging(const char* NAME) {
    cout<<TAG<<" === "<<NAME<<" === "<<endl;
}
#endif

// constructor creates base node
Trie::Trie(){
#ifdef DEBUG
    tagging("Trie()");
#endif
    base = new NodeTrie;
    sizeOfTrie = 0;
};

// remove all nodes from trie
Trie::~Trie(){
#ifdef DEBUG
    tagging("~Trie()");
#endif

    removeAll();
};

// if base node is empty
bool Trie::isEmpty() {
#ifdef DEBUG
    tagging("isEmpty");
#endif

    return NULL == base;
}

// valid year or not
void Trie::checkDigit(int year) {
#ifdef DEBUG
    tagging("add");
#endif

    const int TOO_BIG_YEAR = pow(10, 4) - 1;
    // if incorrect
    if(year < 0 || year > TOO_BIG_YEAR){
        throw (std::invalid_argument("bad argument: not real year"));
    }
}

// add new year to trie
bool Trie::add(int year) {
#ifdef DEBUG
    tagging("add");
#endif
    
    // valid year or not
    checkDigit(year);
    
    vector<int> vect_year;
    digitToVector(vect_year, year);
    
    return addNext(base, vect_year);
}

// transformer
void Trie::digitToVector(vector<int>& v, int counter) {
#ifdef DEBUG
    tagging("digitToVector");
#endif

    if(counter > 0) {
       digitToVector(v, lround(counter / 10));
       
       v.push_back(counter % 10);
    }
}

// add next node to trie
bool Trie::addNext(NodeTrie* digit, vector<int>& vect_year) {
#ifdef DEBUG
    tagging("addNext");
#endif

    // use year from vector
    for (vector<int>::iterator j = vect_year.begin(); j != vect_year.end(); j++) {
        // year is present in trie
        if(!digit->isEmptyChildNode(*j)){
            
            digit = digit->getChildNode(*j);
        }
        
        else {
            NodeTrie* new_node = new NodeTrie;
            // add next year
            digit->setChildNode(new_node, *j);
            digit = digit->getChildNode(*j);
        }
        if(j + 1 == vect_year.end()) {
            // sign the end of year
            digit->setData(true);
            sizeOfTrie++;
            return true;
        }
    }

    return false;
}

// find the year
bool Trie::find(int year) {
#ifdef DEBUG
    tagging("find");
#endif

    // valid year or not
    checkDigit(year);
    
    NodeTrie* digit;
    if (!isEmpty()) {
        digit = base;
    }

    vector<int> vect_year;
    digitToVector(vect_year, year);
    // use year from vector
    for (vector<int>::iterator j = vect_year.begin(); j != vect_year.end(); j++) {
        
        if(digit->isEmptyChildNode(*j)) {
            // year is not found
            return false;
        }
        // find next digit
        else {
            digit = digit->getChildNode(*j);
        }
    }
    
    // return true for whole year
    return digit->getData();
}

// remove year from trie
bool Trie::remove(int year) {
#ifdef DEBUG
    tagging("remove");
#endif
    
    // valid year or not
    checkDigit(year);
    
    NodeTrie* previous;
    NodeTrie* digit;
    if (!isEmpty()) {
        previous = base;
        digit = base;
    }
    
    vector<int> vect_year;
    digitToVector(vect_year, year);
    // use year from vector
    for (vector<int>::iterator j = vect_year.begin(); j != vect_year.end(); j++) {
        // year is present in trie
        if(digit->isEmptyChildNode(*j)){
            // year is not found
            return false;
        }
        else {
            if(j != vect_year.begin()) {
                previous = digit;
            }
            // find next digit
            digit = digit->getChildNode(*j);
        }
        if(j + 1 == vect_year.end()) {
            // free final node
            digit->setData(false);
            sizeOfTrie--;
            int i = 0;
            for(; i < DECIMAL; i++ ){
                // check array of children
                if(digit->isEmptyChildNode(i)) {
                    continue;
                }
                else {
                    break;
                }
            }
            // delete node when is no references
            if(DECIMAL == i){
                delete digit;
                previous->setChildNode(NULL, *j);
            }
            return true;
        }
    }
    
    return false;
}

// get number of data in trie
int Trie::size() {
#ifdef DEBUG
    tagging("size");
#endif
    return sizeOfTrie;
}

// start to remove all nodes in trie
bool Trie::removeAll() {
#ifdef DEBUG
    tagging("removeAll");
#endif

    if(isEmpty()) {
        return false;
    }
    return freePointers(base);
}

// free pointers and remove nodes in trie
bool Trie::freePointers(NodeTrie* digit) {
#ifdef DEBUG
    tagging("freePointers");
#endif

    int j = 0;
    for(; j < DECIMAL; j++ ){
        if(digit->isEmptyChildNode(j)){
            continue;
        }
        // recursively free pointers in child node
        if(!digit->isEmptyChildNode(j)){
            freePointers(digit->getChildNode(j));
            digit->setChildNode(NULL, j);
        }
    }
    // delete node when is no references
    if(DECIMAL == j){
        delete digit;
        return true;
    }
    
    return false;
}

// show all data in trie
void Trie::show() {
#ifdef DEBUG
    tagging("show");
#endif

    showNext(base, 0, 0);
}

// show data in next node
void Trie::showNext(NodeTrie* cursor, int index, int result) {
#ifdef DEBUG
    tagging("showNext");
#endif

    for(int index = 0; index < DECIMAL; index++ )  {
        
        checkNode(cursor, index, result);
    }
}

// check each node and print result
void Trie::checkNode(NodeTrie* cursor, int index, int result) {
#ifdef DEBUG
    tagging("checkNode");
#endif

    // add digit to the result
    if(!cursor->isEmptyChildNode(index))  {
        result = result * 10 + index;
        // print result
        if(cursor->getChildNode(index)->getData()) {
            cout<<result<<endl;
        }
        else {
            showNext(cursor->getChildNode(index), 0, result);
        }
        // delete digit from result
        result = lround(result / 10);
    }
}

//==============================================================

int main(void)
{
    Trie* ts = new Trie();
    cout<<ts->add(2345)<<endl;
    ts->show();
    for(int i = 2000; i < 2015; i++) {
        cout<<i<<" "
            <<ts->add(i)<<endl;
    }
    ts->show();
    cout<<ts->size()<<endl;
    cout<<ts->find(2006)<<endl;
    cout<<ts->find(2016)<<endl;
    cout<<ts->remove(2345)<<endl;
    for(int i = 2000; i < 2015; i++) {
        cout<<i<<" "
            <<ts->remove(i)<<endl;
    }
    cout<<ts->size()<<endl;
    ts->show();
    delete ts;
    
    return 0;
}