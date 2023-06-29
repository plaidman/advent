package one

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

func RunDay(filename string, part string) {
	var file, _ = os.ReadFile("one/" + filename + ".txt")
	var lines = strings.Split(string(file), "\n")

	var parts = make(map[string]func(lines []string))
	parts["one"] = runOne
	parts["two"] = runTwo

	parts[part](lines)
}

func runOne(lines []string) {
	var sum = 0

	for _, line := range lines {
		var value, _ = strconv.Atoi(line)
		sum += value
	}

	fmt.Println(fmt.Sprintf("sum: %d", sum))
}

func runTwo(lines []string) {
	var freqs = make(map[int]bool)
	var sum = 0
	var found = false

	for found == false {
		for i, line := range lines {
			var value, _ = strconv.Atoi(line)
			sum += value

			fmt.Println(fmt.Sprintf("line %d adding %s results in %d", i, line, sum))
			if freqs[sum] {
				found = true
				break
			}

			freqs[sum] = true
		}
	}

	fmt.Println(fmt.Sprintf("saw %d twice", sum))
}
