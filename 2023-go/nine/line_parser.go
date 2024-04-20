package nine

import (
	"regexp"
	"strconv"
)

type LineParser struct {
	linePattern regexp.Regexp
}

func NewLineParser(in chan string) chan []int {
	lp := LineParser{
		linePattern: *regexp.MustCompile(`(-?\d+)`),
	}

	return NewPipelineStep(in, lp.parseLine)
}

func (lp *LineParser) parseLine(in string) []int {
	matches := lp.linePattern.FindAllString(in, -1)
	numbers := make([]int, 0)

	for _, match := range matches {
		number, _ := strconv.Atoi(match)
		numbers = append(numbers, number)
	}

	return numbers
}
