package one

import (
	"fmt"
	"sync"
)

type LineParser struct {
	Out  chan int
	waitGroup sync.WaitGroup
	digits map[string]int
}

func NewLineParser(digits map[string]int) *LineParser {
	return &LineParser{
		make(chan int),
		sync.WaitGroup{},
		digits,
	}
}

func (p *LineParser) WaitForClose() {
	p.waitGroup.Wait()
	close(p.Out)
}

func (p *LineParser) AddLine(line string) {
	p.waitGroup.Add(1)
	go p.parseLine(line)
}

func (p *LineParser) parseLine(line string) {
	defer p.waitGroup.Done()

	tensOut := make(chan int)
	onesOut := make(chan int)

	go p.parseTens(line, tensOut)
	go p.parseOnes(line, onesOut)

	sum := <-tensOut * 10
	sum += <-onesOut

	p.Out <- sum
}

func (p *LineParser) parseTens(line string, out chan int) {
	for i := 0; i < len(line); i++ {
		val, found := p.checkForDigit(line[i:])

		if found {
			out <- val
			return
		}
	}

	panic(fmt.Sprint("didn't find a number: ", line))
}

func (p *LineParser) parseOnes(line string, out chan int) {
	for i := len(line) - 1; i >= 0; i-- {
		val, found := p.checkForDigit(line[i:])

		if found {
			out <- val
			return
		}
	}

	panic(fmt.Sprint("didn't find a number: ", line))
}

func (p *LineParser) checkForDigit(in string) (int, bool) {
	for key, value := range p.digits {
		if len(in) < len(key) {
			continue
		}

		if in[:len(key)] == key {
			return value, true
		}
	}

	return 0, false
}
