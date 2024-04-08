package two

import (
	"sync"
)

type GearMultiplier struct {
	Out       chan int
	in        chan Gear
	waitGroup sync.WaitGroup
	schema    *Schematic
}

func NewGearMultiplier(schema *Schematic, in chan Gear) *GearMultiplier {
	return &GearMultiplier{
		Out:       make(chan int),
		in:        in,
		waitGroup: sync.WaitGroup{},
		schema:    schema,
	}
}

func (gm *GearMultiplier) WaitForClose() {
	gm.waitGroup.Wait()
	close(gm.Out)
}

func (gm *GearMultiplier) WaitForGears() {
	go func() {
		for gear := range gm.in {
			gm.addGear(gear)
		}
	}()
}

func (gm *GearMultiplier) addGear(gear Gear) {
	gm.waitGroup.Add(1)
	go gm.multiplyGear(gear)
}

func (gm *GearMultiplier) multiplyGear(gear Gear) {
	defer gm.waitGroup.Done()

	partNumOut := make(chan int)

	go gm.getPartNum(gear.parts[0], partNumOut)
	go gm.getPartNum(gear.parts[1], partNumOut)

	gm.Out <- (<-partNumOut * <-partNumOut)
}

func (gm *GearMultiplier) getPartNum(part Part, out chan int) {
	out <- gm.schema.GetPartNum(part)
}
