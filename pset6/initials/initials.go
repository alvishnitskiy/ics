package main

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"strings"
)

// get name from user
func getPersonsName() (string, error) {

	// constructs a new Reader
	reader := bufio.NewReader(os.Stdin)

	// get entire string of input
	line, err := reader.ReadString('\n')
	if err != nil {
		return "", err
	}

	return line, nil
}

// extract initials from giving string
func extractInitials(line string, err error) ([]byte, error) {

	// if incorrect
	if err != nil {
		return nil, err
	}

	// splits the string
	field := strings.Fields(line)

	var result []byte
	for _, v := range field {
		// сonverts a string transform character to upper case
		result = append(result, bytes.ToUpper([]byte(v))[0])
	}

	return result, nil
}

// more comfortable
func main() {

	if res, err := extractInitials(getPersonsName()); err != nil {

		fmt.Println(err)
	} else {
		// result with new line
		fmt.Printf("%s\n", res)
	}
}
