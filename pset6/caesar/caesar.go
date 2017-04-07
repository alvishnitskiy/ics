package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

const (
	ALPHABET  = 26
	DIFF_CASE = 32

	A_ASCII = 65
	Z_ASCII = 90

	a_ASCII = 97
	z_ASCII = 122
)

type encryptingString struct {
	// plaintext from user
	plaintext string
	// ciphertext as result
	ciphertext []byte
}

// get plaintext from user
func (es *encryptingString) getPlainText() error {

	fmt.Printf("plaintext: ")

	// constructs a new Reader
	reader := bufio.NewReader(os.Stdin)

	// get entire string of input
	line, err := reader.ReadString('\n')

	if err != nil {
		return err
	}
	// use new string as plaintext
	es.plaintext = line
	return err
}

// encrypting by formula c[i] = (p[i] + k) mod 26
func (es *encryptingString) encryptMessage(k byte) error {

	var err error
	if err = es.getPlainText(); err != nil {
		return err
	}

	fmt.Printf("ciphertext: ")
	// analize each letter
	for _, c := range []byte(es.plaintext) {
		// if is letter
		if c >= A_ASCII && c <= Z_ASCII || c >= a_ASCII && c <= z_ASCII {

			if c, err = changeAlphASCII(k, c); err != nil {
				return err
			}
		}
		// add characters in result
		es.ciphertext = append(es.ciphertext, c)
	}

	return err
}

func main() {

	if len(os.Args) != 2 {

		fmt.Printf("Usage: ./caesar k\n")
		return
	}

	// argument indeed numeric
	key, err := strconv.Atoi(os.Args[1])
	if err != nil {

		fmt.Printf("It’s not indeed numeric.\n")
		return
	}

	es := &encryptingString{}
	if err := es.encryptMessage(byte(key)); err != nil {

		fmt.Println(err)
	} else {
		// result with new line
		fmt.Printf("%s\n", es.ciphertext)
	}
}
