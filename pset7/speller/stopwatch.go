/**
 * Implements a stopwatch.
 */

package main

const SIZE_OF_ARRAY = 4

type Stopwatch struct {
	results [SIZE_OF_ARRAY]float64
}

// get results for report them
func (sw *Stopwatch) getResults(index int) float64 {
	//tagging("getResults")

	return sw.results[index]
}

// determining the time difference
func (sw *Stopwatch) calculate(index int, result float64) int {
	//tagging("calculate(int index)")

	if TIME_TOTAL == index {
		for i := TIME_TOTAL - 1; i >= 0; i-- {
			// total result of all array elements
			sw.results[TIME_TOTAL] += sw.results[i]
		}
	} else {
		// fixing different measurements
		sw.results[index] += result
	}
	return 0
}
