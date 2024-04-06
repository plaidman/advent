package one

import (
	"bufio"
	"fmt"
)

func RunPartTwo(scanner *bufio.Scanner) {
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

	acc.WaitForLines()

	scanner.Split(bufio.ScanLines)
	for scanner.Scan() {
		line := scanner.Text()
		parser.AddLine(line)
	}

	parser.WaitForClose()

	fmt.Println("calibration sum: ", <-acc.SumOut)
}
