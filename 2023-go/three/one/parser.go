package one

import (
	"regexp"
	"sync"
)

type Parser struct {
	Out       chan Part
	schem     *Schematic
	waitGroup sync.WaitGroup
}

func NewParser(schem *Schematic) *Parser {
	return &Parser{
		Out:       make(chan Part),
		schem:     schem,
		waitGroup: sync.WaitGroup{},
	}
}

func (p *Parser) WaitForClose() {
	p.waitGroup.Wait()
	close(p.Out)
}

func (p *Parser) ParseParts() {
	pattern := regexp.MustCompile(`(\d+)`)
	p.schem.ForEachRow(p.addLine(pattern))
}

func (p *Parser) addLine(pattern *regexp.Regexp) func(int, string) {
	return func(rowNum int, line string) {
		p.waitGroup.Add(1)
		go p.parseLine(pattern, rowNum, line)
	}
}

func (p *Parser) parseLine(pattern *regexp.Regexp, rowNum int, line string) {
	defer p.waitGroup.Done()

	matches := pattern.FindAllStringIndex(line, -1)

	for _, match := range matches {
		p.Out <- *NewPart(rowNum, match[0], match[1])
	}
}
