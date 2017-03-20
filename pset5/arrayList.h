// Declares an ArrayList

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

class ArrayList {

private:
    
    // default size of array in memory
    const int SIZE_ON_DEFAULT = 10;
    // for resize of array
    const int TWICE = 2;
    
    const char* TAG = "array_list";
    
    // base element
    int* array;
    // size of array in memory
    int allocated;
    // using size of array
    int sizeOfArray;
    
    // dynamically changing the size of the array
    void rewriteOfArray();
    
    // dynamically changing one element of the array
    void rewriteOfArray(int index);
    
    // deleting temporary arrays
    void deleteArray(int* newArray);
    
    // demonstration of array
    void demoArray(int size);
    
public:

    // debug info
    void tagging(const char* NAME);
    
    // constructor by default
    ArrayList();
    
    // constructor with custom size
    ArrayList(int size);

    // create the array with definite size
    void writeOfArray(int size);

    // free memory thanks destructor
    ~ArrayList();
    
    // write data to the element of array
    void add(int data);
    
    // receive the element of array by index
    int get(int index);
    
    // remove one element from array by index
    int remove(int index);
    
    // display the size of the array in use
    int size();
    
    // free unused elements of array
    void trim();
    
    // display the contents of the array
    void show();
    
    // DEBUG
    void showFull();
};

#endif // ARRAYLIST_H