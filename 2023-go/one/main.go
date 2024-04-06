package one

import (
	"bufio"
	"os"
)

func RunDay(part int, filename string) {
	parts := []func(*bufio.Scanner){
		RunPartOne,
		RunPartTwo,
	}

	file, _ := os.Open(filename)
	scanner := bufio.NewScanner(file)

	partFunc := parts[part-1]
	partFunc(scanner)
}
