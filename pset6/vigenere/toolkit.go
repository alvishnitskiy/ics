package main

import "errors"

// check user input
func getCheckedValue(userValue string) ([]byte, error) {

	charValue := []byte(userValue)

	for _, c := range charValue {

		// generates new error
		if c < A_ASCII || c > Z_ASCII && c < a_ASCII || c > z_ASCII {
			return charValue, errors.New("It's not a letter.\n")
		}
	}
	return charValue, nil
}

// change runes to alphabet numbers
func changeAlph(sym []byte) func() byte {

	for s, _ := range sym {

		if sym[s] >= a_ASCII && sym[s] <= z_ASCII {
			// In the case of small letters 65 ('A') and 32 ('A'...'a') are deducted
			sym[s] -= DIFF_CASE
		}
		// In the case of capital letters 65 ('A') is deducted
		sym[s] -= A_ASCII
	}
	// function provides cyclical getting of keys
	i := 0
	return func() (ret byte) {
		ret = sym[i]

		i = (i + 1) % len(sym)
		return
	}
}

// ASCII => alphabet change => ASCII
func changeAlphASCII(key, sym byte) (byte, error) {

	var lowerСase bool

	lowerСase = sym >= a_ASCII && sym <= z_ASCII
	if lowerСase {
		// In the case of small letters 65 ('A') and 32 ('A'...'a') are deducted
		sym -= DIFF_CASE
	}
	// In the case of capital letters 65 ('A') is deducted
	sym = (sym - A_ASCII + key) % ALPHABET
	sym += A_ASCII

	// Back to small letters
	if lowerСase {
		//sym = unicode.ToLower(sym)
		sym += DIFF_CASE
		return sym, nil
	}
	// For capital letters
	return sym, nil
}
