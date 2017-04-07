package main

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
		sym += DIFF_CASE
		return sym, nil
	}
	// For capital letters
	return sym, nil
}
