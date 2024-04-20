package nine

import (
	"bufio"
	"fmt"
	"os"
)

func RunDay(part int, filename string) {
	lineChan := make(chan string)
	numsChan := NewLineParser(lineChan)
	extrapChan := NewExtrapolator(numsChan, part)
	sumChan := NewSumAccumulator(extrapChan)

	file, _ := os.Open(filename)
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lineChan <- scanner.Text()
	}
	close(lineChan)

	fmt.Println("sum", <-sumChan)
}
