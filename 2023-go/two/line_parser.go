package two

import (
	"fmt"
	"regexp"
	"strconv"
	"sync"
)

type Bag struct {
	id int
	r  int
	g  int
	b  int
}

type BagParser struct {
	Out       chan Bag
	waitGroup sync.WaitGroup
}

func NewBagParser() *BagParser {
	return &BagParser{
		Out:       make(chan Bag),
		waitGroup: sync.WaitGroup{},
	}
}

func (p *BagParser) WaitForClose() {
	p.waitGroup.Wait()
	close(p.Out)
}

func (p *BagParser) AddLine(line string) {
	p.waitGroup.Add(1)
	go p.parseLine(line)
}

func (p *BagParser) parseLine(line string) {
	defer p.waitGroup.Done()

	redOut := make(chan int)
	greenOut := make(chan int)
	blueOut := make(chan int)

	id, remainder := p.extractId(line)

	go p.extractColor(remainder, "red", redOut)
	go p.extractColor(remainder, "green", greenOut)
	go p.extractColor(remainder, "blue", blueOut)

	p.Out <- Bag{id: id, r: <-redOut, g: <-greenOut, b: <-blueOut}
}

func (p *BagParser) extractColor(line string, color string, out chan int) {
	pattern := regexp.MustCompile(fmt.Sprint(`(\d+) `, color))
	matches := pattern.FindAllStringSubmatch(line, -1)
	maxNum := 0

	for _, match := range matches {
		num, _ := strconv.Atoi(match[1])
		maxNum = max(maxNum, num)
	}

	out <- maxNum
}

func (p *BagParser) extractId(line string) (int, string) {
	pattern := regexp.MustCompile(`^Game (\d+): (.*)`)
	matches := pattern.FindStringSubmatch(line)

	id, _ := strconv.Atoi(matches[1])

	return id, matches[2]
}
