package one

import (
	"bufio"
	"fmt"
)

// scanning and processing at the same time byte by byte
// this won't work for the 2nd part, since we need to look for multiple byte words
func RunPartOne(scanner *bufio.Scanner) {
	scanner.Split(bufio.ScanBytes)

	digit := -1
	foundFirst := false
	total := 0
	var char byte

	for scanner.Scan() {
		char = scanner.Bytes()[0]

		if char == '\n' {
			total += digit
			foundFirst = false
		}

		if char >= '0' && char <= '9' {
			digit = int(char - '0')

			if !foundFirst {
				total += digit * 10
				foundFirst = true
			}
		}
	}

	total += digit

	fmt.Println("calibration sum:", total)
}
