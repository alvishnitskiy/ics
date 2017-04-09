/**
 * Implements analyzer words by letters.
 */

package main

import (
	"errors"
	"os"
	"time"
)

const (
	APOSTROPHE_ASCII = 39
	ZERO_ASCII       = 48
	NINE_ASCII       = 57

	A_ASCII = 65
	Z_ASCII = 90

	a_ASCII = 97
	z_ASCII = 122
)

type WordsAudit struct {
	// prepare to spell-check
	index, misspellings, words int
	//word []byte
	word string

	// pointer on using stopwatch
	stopwatch *Stopwatch

	// pointer on default datastructure
	dict *Dictionary
}

// find words and report misspellings
func (wa *WordsAudit) findMisspellings(text *string, checkedWords chan<- string) error {
	//tagging("findMisspellings")

	// try to open text
	fp, err := os.Open(*text)
	if err != nil {
		s := "Could not open " + *text + ".\n"
		err := errors.New(s)
		return err
	}
	// close text
	defer fp.Close()

	// get the file size
	stat, err := fp.Stat()
	if err != nil {
		return err
	}

	// read the file
	bs := make([]byte, stat.Size())
	_, err = fp.Read(bs)
	if err != nil {
		return err
	}

	// spell-check each word in text
	for _, c := range bs {
		// allow only alphabetical characters and apostrophes
		if c >= A_ASCII && c <= Z_ASCII || c >= a_ASCII && c <= z_ASCII ||
			(c == APOSTROPHE_ASCII && wa.index > 0) {
			// alphabetical characters and apostrophes
			wa.alphabetApostrophe(&c)

			// ignore words with numbers (like MS Word can)
		} else if c >= ZERO_ASCII && c <= NINE_ASCII {

			// prepare for new word
			wa.word = ""
			wa.index = 0

			// we must have found a whole word
		} else if wa.index > 0 {
			// find a whole word
			wa.findWholeWord(checkedWords)
		}
	}
	close(checkedWords)
	return nil
}

// alphabetical characters and apostrophes
func (wa *WordsAudit) alphabetApostrophe(c *byte) {
	//tagging("alphabetApostrophe")

	if 0 == wa.index {
		wa.word = ""
	}
	// append character to word
	wa.word += string(*c)
	wa.index++

	// ignore alphabetical strings too long to be words
	if wa.index > LENGTH {

		// prepare for new word
		wa.index = 0
	}
}

// find a whole word and report misspellings
func (wa *WordsAudit) findWholeWord(checkedWords chan<- string) {
	//tagging("foundWholeWord")

	// update counter
	wa.words++

	// check word's spelling
	before := time.Now()
	misspelled := !wa.dict.check(wa.word)
	after := time.Now()

	// update benchmark
	wa.stopwatch.calculate(TIME_CHECK, (after.Sub(before)).Seconds())

	// print word if misspelled
	if misspelled {
		//fmt.Printf("%s\n", wa.word)
		checkedWords <- wa.word
		wa.misspellings++
	}

	// prepare for next word
	wa.index = 0
}

// get number of misspellings for report
func (wa *WordsAudit) getMisspellings() int {
	//tagging("getMisspellings")

	return wa.misspellings
}

// get number of words in text for report
func (wa *WordsAudit) getWords() int {
	//tagging("getWords")

	return wa.words
}

/*
func main() {

	text := "texts/ralph.txt"

	// try to open text
	fp, err := os.Open(text)
	if err != nil {
		fmt.Printf("Could not open %s.\n", text)
		//dict.unload()
		return
	}
	// close text
	defer fp.Close()

	// class for analyze words by letters
	//wordsAudit := &WordsAudit(stopwatch, dict, fp)
	wordsAudit := &WordsAudit{fp: fp}

	// find words and report misspellings
	wordsAudit.findMisspellings()
}*/
