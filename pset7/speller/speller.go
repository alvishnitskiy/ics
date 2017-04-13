/**
 * Implements a spell-checker.
 */

package main

import (
	"fmt"
	"os"
	"runtime"
	"time"
)

const (
	// maximum length for a word
	// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
	LENGTH int = 45
	// default dictionary
	DICTIONARY string = "dictionaries/large"
	DEBUG      bool   = false
)

// enum times
const (
	TIME_LOAD  int = iota // 0
	TIME_CHECK            // 1
	TIME_SIZE             // 2
	TIME_TOTAL            // 3
)

var (
	workers = runtime.NumCPU()
	// name of dictionary file
	dictionary string
	// name of using textfile
	text string
	// pointer on using stopwatch
	stopwatch *Stopwatch
	// pointer on default datastructure
	dict *Dictionary
	// pointer on words analyzer
	wordsAudit *WordsAudit
)

func init() {
	//tagging("init")

	// class for measurement of time
	stopwatch = &Stopwatch{}
	// class with template data structure
	dict = &Dictionary{}
	// class for analyze words by letters
	wordsAudit = &WordsAudit{}
}

// organization of resources to check words
func checking() error {
	//tagging("checking")

	// load dictionary
	err := loadDictionary()
	if err != nil {
		return err
	}
	// check text file
	err = checkText()
	if err != nil {
		return err
	}
	// determine dictionary's size
	n := determineDictionarySize()

	// calculate total time
	stopwatch.calculate(TIME_TOTAL, 0.0)

	// report benchmarks
	reportBenchmarks(wordsAudit.misspellings, n, wordsAudit.words)

	// that's all folks
	return nil
}

// load dictionary
func loadDictionary() error {
	//tagging("loadDictionary")

	before := time.Now()
	err := dict.load()
	after := time.Now()

	// if dictionary not loaded
	if err != nil {
		return err
	}
	// calculate time to load dictionary
	stopwatch.calculate(TIME_LOAD, (after.Sub(before)).Seconds())

	return nil
}

// check text file
func checkText() error {
	//tagging("checkText")

	// check word's spelling
	before := time.Now()
	err := wordsAudit.check()
	after := time.Now()

	// if the check does not work
	if err != nil {
		return err
	}
	// update benchmark
	stopwatch.calculate(TIME_CHECK, (after.Sub(before)).Seconds())

	return nil
}

// report benchmarks
func reportBenchmarks(misspellings int, n uint, words int) {
	//tagging("reportBenchmarks")

	fmt.Print("\n",
		"WORDS MISSPELLED:     ", misspellings, "\n",
		"WORDS IN DICTIONARY:  ", n, "\n",
		"WORDS IN TEXT:        ", words, "\n")
	fmt.Printf("TIME IN load:         %.2f\n", stopwatch.getResults(TIME_LOAD))
	fmt.Printf("TIME IN check:        %.2f\n", stopwatch.getResults(TIME_CHECK))
	fmt.Printf("TIME IN size:         %.2f\n", stopwatch.getResults(TIME_SIZE))
	fmt.Printf("TIME IN TOTAL:        %.2f\n\n", stopwatch.getResults(TIME_TOTAL))
}

func main() {

	lenArgs := len(os.Args)
	// check for correct number of args
	if lenArgs != 2 && lenArgs != 3 {
		fmt.Print("Usage: speller [dictionary] text\n")
		return
	}
	if lenArgs == 3 {
		// determine dictionary to use
		dictionary = os.Args[1]
		// textfile to open text
		text = os.Args[2]

	} else {
		dictionary = DICTIONARY
		text = os.Args[1]
	}
	// organization of resources to check words
	checking()

	// that's all folks
	return
}
