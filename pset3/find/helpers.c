/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <math.h>
#include <assert.h>
#include "helpers.h"

extern const int MAX;

bool recursiveSearch(int, int [], int, int);
bool binarySearch(int, int [], int, int);
bool linearSearch(int, int [], int);
void initBuffer(int [], int [], int);
void emptyBuffer(int [], int [], int);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    // offset from the end of the array
    const int OFFSET = 1;
    int left = 0;
    int right = 0;
    if (n < 0) {
        return false;
    }
    right = n - OFFSET;
    // recursive search
    return recursiveSearch(value, values, left, right);
    // binary search
    //return binarySearch(value, values, left, right);
    // linear search
    //return linearSearch(value, values, n);
}

/**
 * Makes recursive binary search for value in the array.
 */
bool recursiveSearch(int value, int values[], int left, int right)
{
    /*
    OFFSET - offset from the middle of the array
    HALF   - helps to get half of the array
    */
    enum constants { 
        OFFSET = 1, HALF = 2
    };
    int middle = 0;
    if((right - left) < 0){
        return false;
    }
    middle = (int) round((left + right) / HALF);
    if(values[middle] == value){
        return true;
    }
    else {
        if(values[middle] > value){
            right = middle - OFFSET;
        }
        if(values[middle] < value){
            left = middle + OFFSET;
        }
        return recursiveSearch(value, values, left, right);
    }
}

/**
 * Makes binary search for value in the array.
 */
bool binarySearch(int value, int values[], int left, int right)
{
    /*
    OFFSET - offset from the middle of the array
    HALF   - helps to get half of the array
    */
    enum constants { 
        OFFSET = 1, HALF = 2
    };
    int middle = 0;
    while((right - left) >= 0){
        middle = (int) round((left + right) / HALF);
        if(values[middle] == value){
            return true;
        }
        else if(values[middle] > value){
            right = middle - OFFSET;
        }
        else if(values[middle] < value){
            left = middle + OFFSET;
        }
    }
    return false;
}

/**
 * Makes linear search for value in the array.
 */
bool linearSearch(int value, int values[], int n)
{
    for (int i = 0; i < n; i++ ) {
        if(values[i] == value){
            return true;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int buffer [MAX];
    for (int i = 0; i < MAX; i++ ) {
        buffer[i] = 0;
    }
    
    initBuffer(values, buffer, n);
    emptyBuffer(values, buffer, n);
    return;
}

/**
 * Initializing temporary buffer
 */
void initBuffer(int values[], int buffer[], int n)
{
    for (int i = 0; i < n; i++ ) {
        buffer[values[i]]++;
    }
}

/**
 * Empting buffer and transfer values to an array values[]
 */
void emptyBuffer(int values[], int buffer[], int n)
{
    int k = 0;
    for (int i = 0; i < n; i++ ) {
        for (; buffer[k] <= 0; k++ );
        assert(k <= MAX);
        values[i] = k;
        buffer[k]--;
    }
}