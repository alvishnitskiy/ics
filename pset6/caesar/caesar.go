package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"unicode"
)

func main() {

	if len(os.Args) != 2 {

		fmt.Printf("Usage: ./caesar k\n")
		return
	}

	// argument indeed numeric
	if key, err := strconv.Atoi(os.Args[1]); err != nil {

		fmt.Printf("It’s not indeed numeric.")
		return

	} else {
		encryptMessage(rune(key), getPlainText())
	}
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

// encrypting by formula c[i] = (p[i] + k) mod 26
func encryptMessage(k rune, p []rune) {

	fmt.Printf("ciphertext: ")

	for _, c := range p {

		if unicode.IsLetter(c) {

			fmt.Printf("%c", changeAlphASCII(k, c))
		} else {

			fmt.Printf("%c", c)
		}
	}
}

// ASCII => alphabet change => ASCII
func changeAlphASCII(key, sym rune) rune {

	const (
		ALPHABET = 26
		A_ASCII  = 65
	)

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
