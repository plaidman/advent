package one

import (
	"bufio"
	"fmt"
)

func RunPart(scanner *bufio.Scanner) {
	lineIn := make(chan string)
	parserOut := NewCardParser(lineIn)
	scorerOut := NewCardScorer(parserOut)
	accumOut := Accumulate(scorerOut)

	for scanner.Scan() {
		lineIn <- scanner.Text()
	}
	close(lineIn)

	fmt.Println("total score: ", <-accumOut)
}
