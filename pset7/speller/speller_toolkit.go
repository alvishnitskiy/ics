/**
 * Implements a spell-checker.
 */

package main

import (
	"fmt"
	"time"
)

// debug info (sp *Speller)
func tagging(name string) {
	if DEBUG {
		//fmt.Printf("%T === %s ===", sp, name)
		fmt.Printf("=== %s ===", name)
		fmt.Println()
	}
}

// determine dictionary's size (sp *Speller)
func determineDictionarySize(stopwatch *Stopwatch, dict *Dictionary) uint {
	//tagging("determineDictionarySize")

	before := time.Now()
	dictSize := dict.size()
	after := time.Now()

	// calculate time to determine dictionary's size
	stopwatch.calculate(TIME_SIZE, (after.Sub(before)).Seconds())

	return dictSize
}

// check words and get current data
func processChecks(results chan<- map[string]int, dc *Dictionary,
	//tagging("processChecks")

	checkedWords <-chan string) {
	currentData := make(map[string]int)

	for checkedWord := range checkedWords {
		currentData[checkedWord]++
	}
	results <- currentData
}

// integrate all together
func integrate(results <-chan map[string]int, totalForFile map[string]int) {
	//tagging("integrate")

	for i := 0; i < workers; i++ {
		currentData := <-results
		for word, count := range currentData {
			totalForFile[word] += count
		}
	}
}

// representation of all results
func allResults(totalForFile map[string]int) {
	//tagging("allResults")

	// prepare to report misspellings
	fmt.Print("\n", "MISSPELLED WORDS", "\n\n")

	//fmt.Println(totalForFile)
	for word, count := range totalForFile {
		fmt.Printf("%8d %s\n", count, word)
	}
}