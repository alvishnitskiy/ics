// Implements an ArrayList

#include <iostream>
using namespace std;

#include <stdexcept>

#include "arrayList.h"

// create the array with definite size
void ArrayList::writeOfArray(int size)
{
    //tagging("writeOfArray");
    array = new int [size];
    // initialization of the array by zeros
    for(int i = 0; i < size; i++) {
        array[i] = 0;
    }
    
    allocated = size;
    sizeOfArray = 0;
}
    
// dynamically changing the size of the array
void ArrayList::rewriteOfArray() {
    //tagging("rewriteOfArray");
    int* newArray = new int [allocated];
    
    for(int i = 0; i < sizeOfArray; i++) {
        newArray[i] = array[i];
    }
    
    deleteArray(newArray);
}
    
// dynamically changing one element of the array
void ArrayList::rewriteOfArray(int index) {
    //tagging("rewriteOfArray(int index)");
    allocated--;
    int* newArray = new int [allocated];
    for(int i = 0, j = 0; i < sizeOfArray; i++, j++) {
        if(i == index) {
            i++;
        }
        newArray[j] = array[i];
    }
    
    sizeOfArray--;
    
    deleteArray(newArray);
}

// deleting temporary array
void ArrayList::deleteArray(int* newArray) {
    // create temporary array
    int* tmpArray = array;
    array = newArray;
    // free temporary array
    delete [] tmpArray;
}
    
// demonstration of array
void ArrayList::demoArray(int size) {
    //tagging("demoArray");
    for(int i = 0; i < size; i++) {
        cout<<array[i]<<" ";
    }
    cout<<endl;
}
    
// debug info
void ArrayList::tagging(const char* NAME) {
    cout<<TAG<<" === "<<NAME<<" === "<<endl;
}
    
// constructor by default
ArrayList::ArrayList() {
    //tagging("ArrayList()");
    array = new int [SIZE_ON_DEFAULT];
    // dimension by default
    allocated = SIZE_ON_DEFAULT;
    sizeOfArray = 0;
}
    
// constructor with custom size
ArrayList::ArrayList(int size) {
    //tagging("ArrayList(int size)");
    // size = 1 ? sizeOfArray
    if(size < 1) {
        // memory allocation in the range of positive integers
        throw (std::out_of_range("elements in memory less than 1"));
    }
    writeOfArray(size);
}

// free memory thanks destructor
ArrayList::~ArrayList() {
    //tagging("~ArrayList()");
    delete [] array;
}
    
// write data to the element of array
void ArrayList::add(int data) {
    //tagging("add");
    if(sizeOfArray > 0 && allocated == sizeOfArray) {
        allocated *= TWICE;
        rewriteOfArray();
    }
    
    array[sizeOfArray] = data;
    sizeOfArray++;
}
    
// receive the element of array by index
int ArrayList::get(int index) {
    //tagging("get");
    if(index < 0 || index > sizeOfArray){
        // incorrect argument
        throw (std::invalid_argument("bad argument"));
    }
    
    return array[index];
}
    
// remove one element from array by index
int ArrayList::remove(int index) {
    //tagging("remove");
    if(index < 0 || index > sizeOfArray){
        // incorrect argument
        throw (std::invalid_argument("bad argument"));
    }
    
    rewriteOfArray(index);
    
    return index;
}
    
// display the size of the array in use
int ArrayList::size() {
    //tagging("size");
    return sizeOfArray;
}
    
// free unused elements of array
void ArrayList::trim() {
    //tagging("trim");
    allocated = sizeOfArray;
    rewriteOfArray();
}
    
// display the contents of the array
void ArrayList::show() {
    //tagging("show");
    demoArray(sizeOfArray);
}
    
// DEBUG
void ArrayList::showFull() {
    //tagging("showFull");
    demoArray(allocated);
}

int main(void)
{
    ArrayList* arlist = new ArrayList();
    for(int i = 0; i < 15; i++) {
        arlist->add(i);
    }
    cout<<arlist->size()<<endl;
    arlist->show();
    //arlist->showFull();
    cout<<arlist->remove(10)<<endl;
    arlist->show();
    //arlist->showFull();
    arlist->trim();
    //arlist->showFull();
    cout<<arlist->get(5)<<endl;
    //cout<<arlist->get(100)<<endl;
    delete arlist;
    /*ArrayList* arlist2 = new ArrayList(-5);
    arlist2->show();*/
    return 0;
}