/**
 * Implements analyzer words by letters.
 */

package main

import (
	"bufio"
	"errors"
	"fmt"
	"io"
	"os"
	"runtime"
	"strings"
	"unicode"
)

const APOSTROPHE_ASCII = 39

type WordsAudit struct {
	// prepare to spell-check
	misspellings, words int
	//current word
	word string
}

// organaize checking
func (wa *WordsAudit) check() error {
	//tagging("check")

	// Use all the machine's cores
	runtime.GOMAXPROCS(runtime.NumCPU())

	// chanales for misspelings and results
	checkedWords := make(chan string)
	results := make(chan map[string]int)

	// find words and report misspellings
	go readTextFile(checkedWords)
	// parallel processing
	for i := 0; i < workers; i++ {
		go processChecks(results, checkedWords)
	}
	// map for total results
	totalCheck := make(map[string]int)

	getResults(results, totalCheck)
	showMisspellings(totalCheck)

	return nil
}

// find words and report misspellings
func readTextFile(checkedWords chan<- string) error {
	//tagging("findMisspellings")

	// try to open text
	fp, err := os.Open(text)
	if err != nil {
		s := "Could not open " + text + ".\n"
		err := errors.New(s)
		return err
	}
	// close text
	defer fp.Close()

	bufferedReader := bufio.NewReader(fp)
	// until the end of file
	for {
		bs, _, err := bufferedReader.ReadLine()
		//str, err := bufferedReader.ReadString('\n')
		str := string(bs)
		if err != nil {
			if err != io.EOF {
				// in the case of a real error
				return err
			}
			break
		}
		for _, wordsAudit.word = range strings.FieldsFunc(str,
			func(char rune) bool {
				return !unicode.IsLetter(char) && !(APOSTROPHE_ASCII == char)
			}) {

			wordsAudit.findMisspellings(checkedWords)
			//checkedWords <- word
		}
	}
	close(checkedWords)
	return nil
}

// find a whole word and report misspellings
func (wa *WordsAudit) findMisspellings(checkedWords chan<- string) {
	//tagging("foundWholeWord")

	// update counter
	wa.words++
	// check word's spelling
	misspelled := !dict.find(wa.word)

	// print word if misspelled
	if misspelled {

		checkedWords <- wa.word
		wa.misspellings++
	}
}

// check words and get current data
func processChecks(results chan<- map[string]int, checkedWords <-chan string) {
	//tagging("processChecks")

	currentData := make(map[string]int)

	for checkedWord := range checkedWords {
		currentData[checkedWord]++
	}
	results <- currentData
}

// get all together
func getResults(results <-chan map[string]int, totalCheck map[string]int) {
	//tagging("integrate")

	for i := 0; i < workers; i++ {
		currentData := <-results

		for word, count := range currentData {
			totalCheck[word] += count
		}
	}
}

// representation of all misspellings
func showMisspellings(totalCheck map[string]int) {
	//tagging("allResults")

	// prepare to report misspellings
	fmt.Print("\n", "MISSPELLED WORDS", "\n\n")

	//fmt.Println(totalCheck)
	for word, count := range totalCheck {
		fmt.Printf("%8d %s\n", count, word)
	}
}
