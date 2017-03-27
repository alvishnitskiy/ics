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
    this->is_word = false;
    // free child references
    for(int j = 0; j < ALPH_APOS; j++ ){
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
    //tagging("isEmptyChildNode");
#endif
    return NULL == this->children[index];
}

// get inner data
int NodeTrie::getData() {
#ifdef DEBUG
    //tagging("getData");
#endif
    return this->is_word;
}

// assigned to inner data
void NodeTrie::setData(bool year) {
#ifdef DEBUG
    //tagging("setData");
#endif
    this->is_word = year;
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

// add new word to trie
bool Trie::add(const char* word) {
#ifdef DEBUG
    tagging("add");
#endif
    
    return addNext(base, word);
}

// add next node to trie
bool Trie::addNext(NodeTrie* letter, const char* word) {
#ifdef DEBUG
    tagging("addNext");
#endif

    int i = 0;
    for(; word[i] != '\0'; i++ ) {

        int j = changeAlphApos(word[i]);
        // letter is present in trie
        if(!letter->isEmptyChildNode(j)){
            letter = letter->getChildNode(j);
            continue;
        }
        else {
            NodeTrie* new_node = new NodeTrie;
            // add next letter
            letter->setChildNode(new_node, j);
            letter = letter->getChildNode(j);
        }
    }
    if(i > 0) {
        // sign the end of word
        letter->setData(true);
        sizeOfTrie++;
        return true;
    }

    return false;
}

// change alphabet and apostrophe to char code
int Trie::changeAlphApos(char sym) {
#ifdef DEBUG
    //tagging("changeAlphApos");
#endif

    enum constants {
        APOSTROPHE = 26, DIFF_CASE = 32, A_ASCII = 65
    };
    if(sym >= A_ASCII + DIFF_CASE) {
        // In the case of small letters 65 ('A') and 32 ('A'...'a') are deducted
        sym -= DIFF_CASE;
    }
    if(sym < A_ASCII) {
        return APOSTROPHE;
    }
    // In the case of capital letters 65 ('A') is deducted
    return sym - A_ASCII;
}

// change char code to alphabet and apostrophe
char Trie::changeCharCode(int sym) {
#ifdef DEBUG
    //tagging("changeCharCode");
#endif

    enum constants {
        APOSTROPHE = 26, APOSTROPHE_ASCII = 39, A_ASCII = 65
    };
    if(sym == APOSTROPHE) {
        return APOSTROPHE_ASCII;
    }
    // makes all letters capital
    return sym + A_ASCII;
}

// find the word
bool Trie::find(const char* word) {
#ifdef DEBUG
    tagging("find");
#endif

    NodeTrie* letter;
    if (!isEmpty()) {
        letter = base;
    }
    
    for(int i = 0; word[i] != '\0'; i++ ) {
        
        int j = changeAlphApos(word[i]);
        
        if(letter->isEmptyChildNode(j)) {
            // word is not found
            return false;
        }
        // find next letter
        if(!letter->isEmptyChildNode(j)) {
            letter = letter->getChildNode(j);
        }
    }
    
    // return true for whole word
    return letter->getData();
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
bool Trie::freePointers(NodeTrie* letter) {
#ifdef DEBUG
    tagging("freePointers");
#endif

    int j = 0;
    for(; j < ALPH_APOS; j++ ){
        if(letter->isEmptyChildNode(j)){
            continue;
        }
        // recursively free pointers in child node
        if(!letter->isEmptyChildNode(j)){
            freePointers(letter->getChildNode(j));
            letter->setChildNode(NULL, j);
        }
    }
    // delete node when is no references
    if(ALPH_APOS == j){
        delete letter;
        if(letter == base) {
            base = NULL;
        }
        return true;
    }
    
    return false;
}

// show all data in trie
void Trie::show() {
#ifdef DEBUG
    tagging("show");
#endif

    char result[50] = "";
    showNext(base, result, 0);
}

// show data in next node
void Trie::showNext(NodeTrie* letter, char result[], int cursor) {
#ifdef DEBUG
    tagging("showNext");
#endif

    for(int index = 0; index < ALPH_APOS; index++ ) {
        
        checkNode(letter, index, result, cursor);
    }
}

// check each node and print result
void Trie::checkNode(NodeTrie* letter, int index, char result[], int cursor) {
#ifdef DEBUG
    tagging("checkNode");
#endif
    // input character to the result string
    if(!letter->isEmptyChildNode(index))  {
        result[cursor] = changeCharCode(index);
        // print result
        if(letter->getChildNode(index)->getData()) {
            cout<<result<<endl;
        }
        else {
            cursor++;
            showNext(letter->getChildNode(index), result, cursor);
            // delete character from result string
            result[cursor] = (char) 0;
        }
    }
}

//==============================================================
/*
int main(void)
{
    Trie* ts = new Trie();
    cout<<ts->add("Hello")<<endl;
    cout<<ts->add("ice")<<endl;
    cout<<ts->add("number")<<endl;
    cout<<ts->add("bool")<<endl;
    ts->show();
    cout<<ts->add("whole")<<endl;
    cout<<ts->add("world")<<endl;
    cout<<ts->add("skyfall")<<endl;
    cout<<ts->add("white")<<endl;
    cout<<ts->size()<<endl;
    ts->show();
    cout<<ts->find("world")<<endl;
    delete ts;
    
    return 0;
}*/