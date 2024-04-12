package two

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

	cards := <-accumOut
	total := 0
	for i := 0; i < len(cards); i++ {
		card := cards[i]

		for j := 0; j < card.score; j++ {
			fmt.Printf("adding %v copies to card %v\n", card.copies, cards[i+j+1].id)
			cards[i+j+1].copies += card.copies
		}

		fmt.Println(card)
		total += card.copies
	}

	fmt.Println(total, "cards total")
}
