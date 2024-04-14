package one

import (
	"bufio"
	"fmt"
	"sort"
)

func RunPart(scanner *bufio.Scanner) {
	lineChan := make(chan string)
	handChan := NewHandParser(lineChan)
	rankChan := NewHandRanker(handChan)
	allHandsChan := NewSliceAccumulator(rankChan)

	for scanner.Scan() {
		line := scanner.Text()
		lineChan <- line
	}
	close(lineChan)

	allHands := <-allHandsChan
	sort.Slice(allHands, SortHandFunc(allHands))

	sum := 0
	for i, hand := range allHands {
		sum += (i+1) * hand.bid
	}

	fmt.Println("winnings:", sum)
}
