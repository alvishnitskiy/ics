/**
 * Declares and implements in template a dictionary's functionality.
 */

package main

import (
	"bufio"
	"errors"
	"io"
	"os"
	"strings"
)

type Dictionary struct {
	// default datastructure
	dataStruct map[string]int
	// number of data in map
	sizeOfMap uint
}

// Returns true if word is in dictionary else false.
func (dc *Dictionary) find(word string) bool {
	//tagging("check")

	// find the word in default datastructure
	_, found := dc.dataStruct[strings.ToLower(word)]
	return found
}

// Loads dictionary into memory. Returns true if successful else false.
func (dc *Dictionary) load() error {
	//tagging("load")

	// initialization of dictionary
	dc.dataStruct = make(map[string]int)

	err := readWords()
	if err != nil {
		return err
	}

	return nil
}

// read dictionary file by words
func readWords() error {
	//tagging("readWords")

	// open dictionary file
	dictptr, err := os.Open(dictionary)
	if err != nil {

		s := "Could not open " + dictionary + ".\n"
		err := errors.New(s)
		return err
	}
	// close dictionary file
	defer dictptr.Close()

	bufferedReader := bufio.NewReader(dictptr)
	// until the end of file
	for {
		bs, _, err := bufferedReader.ReadLine()
		//tmp_word, err := bufferedReader.ReadString('\n')
		if err != nil {
			if err != io.EOF {
				// in the case of a real error
				return err
			}
			break
		}
		tmp_word := string(bs)
		if tmp_word != "" {

			dict.add(tmp_word)
		}
	}
	return nil
}

// add word to the data structure
func (dc *Dictionary) add(word string) {
	//tagging("add")

	dc.dataStruct[word]++
	dc.sizeOfMap++
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded.
func (dc *Dictionary) size() uint {
	//tagging("size")

	// get number of words in datastructure
	return dc.sizeOfMap
}
