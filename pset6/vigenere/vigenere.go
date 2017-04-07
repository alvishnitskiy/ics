package main

import (
	"bufio"
	"errors"
	"fmt"
	"os"
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

// encrypting by formula c[i] = (p[i] + k[j]) mod 26
func (es *encryptingString) encryptMessage(k []byte) error {

	var err error
	if err = es.getPlainText(); err != nil {
		return err
	}
	// variable as function to get keys
	keyInt := changeAlph(k)

	fmt.Printf("ciphertext: ")
	// analize each letter
	for _, c := range []byte(es.plaintext) {
		// if is letter
		if c >= A_ASCII && c <= Z_ASCII || c >= a_ASCII && c <= z_ASCII {

			if c, err = changeAlphASCII(keyInt(), c); err != nil {
				return err
			}
		}
		// add characters in result
		es.ciphertext = append(es.ciphertext, c)
	}

	return err
}

func main() {

	err := errors.New("Usage: ./vigenere k\n")

	if len(os.Args) == 2 {
		// get checked keys
		var key []byte
		key, err = getCheckedValue(os.Args[1])

		if err == nil {
			//encryptMessage(key, getPlainText())
			es := &encryptingString{}

			if err := es.encryptMessage(key); err == nil {
				// result with new line
				fmt.Printf("%s\n", es.ciphertext)
			}
			return
		}
	}
	//else
	if err != nil {
		fmt.Print(err)
	}
}
