package three

import (
	"bufio"
	"os"

	"2023-go/three/one"
)

func RunDay(part int, filename string) {
	parts := []func(*bufio.Scanner){
		one.RunPartOne,
	}

	file, _ := os.Open(filename)
	scanner := bufio.NewScanner(file)

	partFunc := parts[part-1]
	partFunc(scanner)
}
