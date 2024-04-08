package two

import (
	"sync"
)

type PartParser struct {
	Out       chan Gear
	in        chan Gear
	waitGroup sync.WaitGroup
	schema    *Schematic
}

func NewPartParser(schema *Schematic, in chan Gear) *PartParser {
	return &PartParser{
		Out:       make(chan Gear),
		in:        in,
		waitGroup: sync.WaitGroup{},
		schema:    schema,
	}
}

func (pp *PartParser) WaitForClose() {
	pp.waitGroup.Wait()
	close(pp.Out)
}

func (pp *PartParser) WaitForGears() {
	go func() {
		for gear := range pp.in {
			pp.addGear(gear)
		}
	}()
}

func (pp *PartParser) addGear(gear Gear) {
	pp.waitGroup.Add(1)
	go pp.parseParts(gear)
}

func (pp *PartParser) parseParts(gear Gear) {
	defer pp.waitGroup.Done()

	partOut := make(chan Part)

	go pp.parsePart(gear.parts[0], partOut)
	go pp.parsePart(gear.parts[1], partOut)

	gear.parts[0] = <- partOut
	gear.parts[1] = <- partOut

	pp.Out <- gear
}

func (pp *PartParser) parsePart(part Part, out chan Part) {
	out <- pp.schema.ParsePart(part)
}
