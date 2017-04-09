/**
 * Declares and implements in template a dictionary's functionality.
 */

package main

import (
	"runtime"
	"sync"
)

var workers = runtime.NumCPU()

type Dictionary struct {
	// default datastructure
	dataStruct map[rune]string
	// number of data in map
	sizeOfMap uint

	mutex *sync.RWMutex
}

// Returns true if word is in dictionary else false.
func (dc *Dictionary) check(word string) bool {
	//tagging("check")

	// find the word in default datastructure
	v, found := dc.dataStruct[hash(word)]
	return found && v == word
}

// Loads dictionary into memory. Returns true if successful else false.
func (dc *Dictionary) load(dictionary string) error {
	//tagging("load")

	// Use all the machine's cores
	runtime.GOMAXPROCS(runtime.NumCPU())

	// chanales for words and boolean finish
	words := make(chan string, workers*4)
	done := make(chan bool, workers)

	// initialization of dictionary
	dc.dataStruct = make(map[rune]string)
	dc.mutex = new(sync.RWMutex)

	go readWords(dictionary, words)
	processWords(done, dc, words)
	waitUntil(done)

	return nil
}

// add word to the data structure
func (dc *Dictionary) add(word string) {
	//tagging("add")

	dc.mutex.Lock()
	defer dc.mutex.Unlock()

	dc.dataStruct[hash(word)] = word
	dc.sizeOfMap++
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded.
func (dc *Dictionary) size() uint {
	//tagging("size")

	// get number of words in datastructure
	return dc.sizeOfMap
}
