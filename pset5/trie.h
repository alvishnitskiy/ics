/**
 * Declares a trie's functionality.
 */

#ifndef TRIE_H
#define TRIE_H

#include <math.h>
#include <vector>

// 10 digits from 0 to 9
#define DECIMAL 10

class NodeTrie {
    
private:

    // sign the end of year
    bool is_year;
    
    // array of child references
    NodeTrie* children[DECIMAL];

    const char* TAG = "node";

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
    void setData(bool year);
    
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
    
    // valid year or not
    void checkDigit(int year);
    
    // transformer
    void digitToVector(std::vector<int>& v, int counter);
    
    // add next node to trie
    bool addNext(NodeTrie* digit, std::vector<int>& v);
    
    // free pointers and remove nodes in trie
    bool freePointers(NodeTrie* digit);
    
    // show data in next node
    void showNext(NodeTrie* cursor, int index, int result);
    
    // check each node and print result
    void checkNode(NodeTrie* cursor, int index, int result);

public:

    // debug info
    void tagging(const char* NAME);
    
    // constructor creates base node
    Trie();
    
    // remove all nodes from trie
    ~Trie();
    
    // if base node is empty
    bool isEmpty();
    
    // add new year to trie
    bool add(int year);
    
    // find the year
    bool find(int year);
    
    // remove node by index
    bool remove(int year);
    
    // get number of data in trie
    int size();
    
    // start to remove all nodes in trie
    bool removeAll();
    
    // show all data in trie
    void show();
};

#endif // TRIE_H
