package two

import (
	"fmt"
	"os"
	"strings"
)

func RunDay(filename string, part string) {
	var file, _ = os.ReadFile("two/" + filename + ".txt")
	var lines = strings.Split(string(file), "\n")

	var parts = make(map[string]func(lines []string))
	parts["one"] = runOne
	parts["two"] = runTwo

	parts[part](lines)
}

func runOne(lines []string) {
	var numThrees, numTwos = 0, 0

	for _, line := range lines {
		var letterMap = make(map[rune]int)

		for _, letter := range line {
			letterMap[letter]++
		}

		var foundTwo, foundThree = processLetterMap(letterMap)

		if foundTwo {
			numTwos++
		}

		if foundThree {
			numThrees++
		}
	}

	fmt.Println(fmt.Sprintf("%d * %d = %d", numTwos, numThrees, numTwos*numThrees))
}

func processLetterMap(letterMap map[rune]int) (bool, bool) {
	var foundTwo, foundThree = false, false

	for _, count := range letterMap {
		if count == 2 {
			foundTwo = true
		}

		if count == 3 {
			foundThree = true
		}
	}

	return foundTwo, foundThree
}

func runTwo(lines []string) {
	for i, line := range lines {
		for j := i + 1; j < len(lines); j++ {
			var diff = countDiff(line, lines[j])
			if diff == 1 {
				fmt.Println(fmt.Sprintf("%s and %s", line, lines[j]))
			}
		}
	}
}

func countDiff(lineOne string, lineTwo string) int {
	var countDiff = 0

	for i, char := range lineOne {
		if char != rune(lineTwo[i]) {
			countDiff++
		}
	}

	return countDiff
}
