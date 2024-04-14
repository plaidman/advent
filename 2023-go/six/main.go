package six

import (
	"bufio"
	"os"

	"2023-go/six/one"
	"2023-go/six/two"
)

func RunDay(part int, filename string) {
	parts := []func(*bufio.Scanner){
		one.RunPart,
		two.RunPart,
	}

	file, _ := os.Open(filename)
	scanner := bufio.NewScanner(file)

	partFunc := parts[part-1]
	partFunc(scanner)
}
