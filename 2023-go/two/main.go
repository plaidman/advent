package two

import (
	"bufio"
	"fmt"
	"os"
)

func RunDay(part int, filename string) {
	file, _ := os.Open(filename)
	scanner := bufio.NewScanner(file)

	parser := NewBagParser()

	var accum *Accumulator[Bag, int]
	switch part {
	case 1:
		accum = NewPartOneAccumulator(parser.Out)
	case 2:
		accum = NewPartTwoAccumulator(parser.Out)
	}

	accum.WaitForData()

	scanner.Split(bufio.ScanLines)
	for scanner.Scan() {
		line := scanner.Text()
		parser.AddLine(line)
	}

	parser.WaitForClose()

	fmt.Println("power sum: ", <- accum.Out)
}
