/**
 * Declares a trie's functionality.
 */

#ifndef TRIE_H
#define TRIE_H

#include <string.h>

// 26 letters of the alphabet plus an apostrophe
#define ALPH_APOS 27

class NodeTrie {
    
private:

    // sign the end of word
    bool is_word;
    
    // array of child references
    NodeTrie* children[ALPH_APOS];

    const char* TAG = "node_trie";

public:
    
    // debug info
    void tagging(const char* NAME);
    
    // clean start settings
    NodeTrie();
    
    // destructor for debug
    ~NodeTrie();
    
    // if child node is empty
    bool isEmptyChildNode(int index);
    
    // get inner data
    int getData();
    
    // assigned to inner data
    void setData(bool word);
    
    // return child node
    NodeTrie* getChildNode(int index);
    
    // assigned child node
    void setChildNode(NodeTrie* node, int index);
};

//==============================================================

class Trie {

private:
    
    // root node in trie
    NodeTrie* base;
        
    // number of data in trie
    int sizeOfTrie;
    
    const char* TAG = "trie";
    
    // add next node to trie
    bool addNext(NodeTrie* letter, const char* word);
    
    // change alphabet and apostrophe to char code
    int changeAlphApos(char);
    
    // change char code to alphabet and apostrophe
    char changeCharCode(int sym);
    
    // free pointers and remove nodes in trie
    bool freePointers(NodeTrie* letter);
    
    // show data in next node
    void showNext(NodeTrie* letter, char* result, int cursor);
    
    // check each node and print result
    void checkNode(NodeTrie* letter, int index, char result[], int cursor);

public:

    // debug info
    void tagging(const char* NAME);
    
    // constructor creates base node
    Trie();
    
    // remove all nodes from trie
    ~Trie();
    
    // if base node is empty
    bool isEmpty();
    
    // add new word to trie
    bool add(const char* word);
    
    // find the word
    bool find(const char* word);
    
    // get number of data in trie
    int size();
    
    // start to remove all nodes in trie
    bool removeAll();

    // show all data in trie
    void show();
};

#endif // TRIE_H
