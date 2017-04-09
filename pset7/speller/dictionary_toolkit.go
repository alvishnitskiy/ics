/**
 * Declares and implements in template a dictionary's functionality.
 */

package main

import (
	"bufio"
	"errors"
	"io"
	"os"
)

//var workers = runtime.NumCPU()

// read dictionary file by words
func readWords(dictionary string, words chan<- string) error {
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
		tmp_word, err := bufferedReader.ReadString('\n')
		if tmp_word != "" {
			tmp_word = tmp_word[:len(tmp_word)-1]

			words <- tmp_word
		}
		if err != nil {
			if err != io.EOF {
				// in the case of a real error
				return err
			}
			break
		}
	}
	close(words)
	return nil
}

// cicle by dictionary words
func processWords(done chan<- bool, dc *Dictionary, words <-chan string) {
	//tagging("processWords")

	for i := 0; i < workers; i++ {
		go func() {
			for word := range words {
				dc.add(word)
			}
			done <- true
		}()
	}
}

// wait until all work will be done
func waitUntil(done <-chan bool) {
	//tagging("waitUntil")

	for i := 0; i < workers; i++ {
		<-done
	}
}

/**
 * A hash routine for string objects.
 * The source of information:
 * Weiss, Mark Allen.
 *    Data structures and algorithm analysis in C++ / Mark Allen Weiss, Florida International University
 */
func hash(key string) rune {
	//tagging("hash")

	const POLYNOM = 37
	var hashVal rune
	// The code computes a polynomial function (of 37) by use of Horner’s rule.

	for _, ch := range []rune(key) {
		hashVal = POLYNOM*hashVal + ch
	}

	return hashVal
}
