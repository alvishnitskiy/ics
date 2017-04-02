package main

import (
	"bufio"
	"errors"
	"fmt"
	"os"
	"unicode"
)

const (
	ALPHABET = 26
	A_ASCII  = 65
)

func main() {

	if len(os.Args) == 2 {
		// get checked keys
		if key, err := getCheckedValue(os.Args[1]); err == nil {

			encryptMessage(key, getPlainText())
			return
		}
	}
	//else
	fmt.Printf("Usage: ./vigenere k\n")
}

// check user input
func getCheckedValue(userValue string) ([]rune, error) {

	charValue := []rune(userValue)

	for _, c := range charValue {

		// generates new error
		if !unicode.IsLetter(c) {
			return charValue, errors.New("Is not a letter")
		}
	}
	return charValue, nil
}

// get plaintext from user
func getPlainText() []rune {

	fmt.Printf("plaintext: ")

	// constructs a new Reader
	reader := bufio.NewReader(os.Stdin)

	// get entire string of input
	line, err := reader.ReadString('\n')
	if err != nil {

		fmt.Printf("Incorrect input.")
		os.Exit(1)
	}
	//return line
	return []rune(line)
}

// encrypting by formula c[i] = (p[i] + k[j]) mod 26
func encryptMessage(k, p []rune) {

	// variable as function to get keys
	keyInt := changeAlph(k)

	fmt.Printf("ciphertext: ")
	for _, c := range p {

		if unicode.IsLetter(c) {

			fmt.Printf("%c", changeAlphASCII(keyInt(), c))
		} else {

			fmt.Printf("%c", c)
		}
	}
}

// change runes to alphabet numbers
func changeAlph(sym []rune) func() rune {

	for s, _ := range sym {

		if unicode.IsLower(sym[s]) {
			// In the case of small letters 65 ('A') and 32 ('A'...'a') are deducted
			sym[s] = unicode.ToUpper(sym[s])
		}
		// In the case of capital letters 65 ('A') is deducted
		sym[s] -= A_ASCII
	}
	// function provides cyclical getting of keys
	i := 0
	return func() (ret rune) {
		ret = sym[i]

		i = (i + 1) % len(sym)
		return
	}
}

// ASCII => alphabet change => ASCII
func changeAlphASCII(key, sym rune) rune {

	var lowerСase bool

	lowerСase = unicode.IsLower(sym)
	if lowerСase {
		// In the case of small letters 65 ('A') and 32 ('A'...'a') are deducted
		sym = unicode.ToUpper(sym)
	}
	// In the case of capital letters 65 ('A') is deducted
	sym = (sym - A_ASCII + key) % ALPHABET
	sym += A_ASCII

	// Back to small letters
	if lowerСase {
		sym = unicode.ToLower(sym)
		return sym
	}
	// For capital letters
	return sym
}
