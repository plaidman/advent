package two

import (
	"regexp"
	"sync"
)

type GearParser struct {
	Out       chan Gear
	waitGroup sync.WaitGroup
	schema    *Schematic
}

func NewGearParser(schema *Schematic) *GearParser {
	return &GearParser{
		Out:       make(chan Gear),
		waitGroup: sync.WaitGroup{},
		schema: schema,
	}
}

func (gp *GearParser) WaitForClose() {
	gp.waitGroup.Wait()
	close(gp.Out)
}

func (gp *GearParser) FindGears() {
	pattern := regexp.MustCompile(`(\*)`)
	gp.schema.ForEachRow(gp.addLine(pattern))
}

func (gp *GearParser) addLine(pattern *regexp.Regexp) func(int, string) {
	return func(rowNum int, line string) {
		gp.waitGroup.Add(1)
		go gp.parseLine(pattern, rowNum, line)
	}
}

func (gp *GearParser) parseLine(pattern *regexp.Regexp, rowNum int, line string) {
	defer gp.waitGroup.Done()

	matches := pattern.FindAllStringIndex(line, -1)

	for _, match := range matches {
		gp.Out <- *NewGear(rowNum, match[0])
	}
}
