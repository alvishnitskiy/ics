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

type Speller struct {
	// name of dictionary file
	dictionary *string
	// name of using textfile
	text *string
}

// organization of resources to check words
func (sp *Speller) checking() error {
	//tagging("checking")

	// class for measurement of time
	stopwatch := &Stopwatch{}

	// class with template data structure
	dict := &Dictionary{}

	// load dictionary
	err := sp.loadDictionary(stopwatch, dict)
	if err != nil {
		return err
	}
	// class for analyze words by letters
	wordsAudit := &WordsAudit{stopwatch: stopwatch, dict: dict}

	// check text file
	err = sp.checkText(wordsAudit)
	if err != nil {
		return err
	}
	// determine dictionary's size
	n := determineDictionarySize(stopwatch, dict)

	// calculate total time
	stopwatch.calculate(TIME_TOTAL, 0.0)

	// report benchmarks
	sp.reportBenchmarks(stopwatch, wordsAudit.getMisspellings(), n, wordsAudit.getWords())

	// that's all folks
	return nil
}

// load dictionary
func (sp *Speller) loadDictionary(stopwatch *Stopwatch, dict *Dictionary) error {
	//tagging("loadDictionary")

	before := time.Now()
	err := dict.load(*sp.dictionary)
	after := time.Now()

	// abort if dictionary not loaded
	if err != nil {
		return err
	}

	// calculate time to load dictionary
	stopwatch.calculate(TIME_LOAD, (after.Sub(before)).Seconds())

	return nil
}

// check text file
func (sp *Speller) checkText(wordsAudit *WordsAudit) error {
	//tagging("checkText")

	// Use all the machine's cores
	runtime.GOMAXPROCS(runtime.NumCPU())

	// chanales for misspelings and results
	checkedWords := make(chan string, workers*4)
	results := make(chan map[string]int, workers)

	// find words and report misspellings
	go wordsAudit.findMisspellings(sp.text, checkedWords)

	for i := 0; i < workers; i++ {
		go processChecks(results, wordsAudit.dict, checkedWords)
	}
	//totalForFile := make([]string, 10)
	totalForFile := make(map[string]int)
	integrate(results, totalForFile)
	allResults(totalForFile)

	return nil
}

// report benchmarks
func (sp *Speller) reportBenchmarks(stopwatch *Stopwatch, misspellings int, n uint, words int) {
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

	var dictionary, text string

	if lenArgs == 3 {
		// determine dictionary to use
		dictionary = os.Args[1]
		// try to open text
		text = os.Args[2]

	} else {
		dictionary = DICTIONARY
		text = os.Args[1]
	}

	// organization of spell-checking with definite dictionary and textfile
	speller := &Speller{dictionary: &dictionary, text: &text}

	// organization of resources to check words
	speller.checking()

	// that's all folks
	return
}
