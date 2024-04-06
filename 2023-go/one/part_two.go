package one

import (
	"bufio"
	"fmt"
)

func RunPartTwo(scanner *bufio.Scanner) {
	// NOTE: part one can be solved by only including the digits here
	//  the other implementation is interesting enough that I wanted to keep it
	//  also the old implementation is ~11x faster
	//  old: ~200µs
	//  new: ~2.2ms

	var digits = map[string]int{
		"1": 1, "one": 1,
		"2": 2, "two": 2,
		"3": 3, "three": 3,
		"4": 4, "four": 4,
		"5": 5, "five": 5,
		"6": 6, "six": 6,
		"7": 7, "seven": 7,
		"8": 8, "eight": 8,
		"9": 9, "nine": 9,
	}

	parser := NewLineParser(digits)
	acc := NewSumAccumulator(parser.Out)

	acc.WaitForData()

	scanner.Split(bufio.ScanLines)
	for scanner.Scan() {
		line := scanner.Text()
		parser.AddLine(line)
	}

	parser.WaitForClose()

	fmt.Println("calibration sum: ", <-acc.Out)
}
