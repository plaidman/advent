package two

import (
	"sync"
)

type GearFilter struct {
	Out       chan Gear
	in        chan Gear
	waitGroup sync.WaitGroup
	schema    *Schematic
}

func NewGearFilter(schema *Schematic, in chan Gear) *GearFilter {
	return &GearFilter{
		Out:       make(chan Gear),
		in:        in,
		waitGroup: sync.WaitGroup{},
		schema:    schema,
	}
}

func (gf *GearFilter) WaitForClose() {
	gf.waitGroup.Wait()
	close(gf.Out)
}

func (gf *GearFilter) WaitForGears() {
	go func() {
		for gear := range gf.in {
			gf.addGear(gear)
		}
	}()
}

func (gf *GearFilter) addGear(gear Gear) {
	gf.waitGroup.Add(1)
	go gf.filterGear(gear)
}

func (gf *GearFilter) filterGear(gear Gear) {
	defer gf.waitGroup.Done()

	parts := gf.schema.GearParts(gear)
	if len(parts) != 2 {
		return
	}

	gear.AddParts(parts)
	gf.Out <- gear
}
