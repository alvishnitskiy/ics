package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"unicode"
)

// more comfortable
func main() {

	extractInitials(getPersonsName())
}

// get name from user
func getPersonsName() string {

	// constructs a new Reader
	reader := bufio.NewReader(os.Stdin)

	// get entire string of input
	line, err := reader.ReadString('\n')
	if err != nil {

		fmt.Printf("Incorrect input.")
		os.Exit(1)
	}

	return line
}

// extract initials from giving string
func extractInitials(line string) {

	// splits the string
	fild := strings.Fields(line)
	for _, v := range fild {

		// сonverts a string into a slice of characters
		// and gets the first character
		if c := []rune(v)[0]; unicode.IsLetter(c) {

			// transform character to upper case
			fmt.Printf("%c", unicode.ToUpper(c))
		}
	}
	// new line
	fmt.Println()
}
