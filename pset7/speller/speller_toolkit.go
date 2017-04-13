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
func determineDictionarySize() uint {
	//tagging("determineDictionarySize")

	before := time.Now()
	dictSize := dict.size()
	after := time.Now()

	// calculate time to determine dictionary's size
	stopwatch.calculate(TIME_SIZE, (after.Sub(before)).Seconds())

	return dictSize
}
