package two

import (
	"bufio"
	"fmt"
)

func RunPart(scanner *bufio.Scanner) {
	schema := NewSchematic()
	gearParser := NewGearParser(schema)
	gearFilter := NewGearFilter(schema, gearParser.Out)
	partParser := NewPartParser(schema, gearFilter.Out)
	gearMultiplier := NewGearMultiplier(schema, partParser.Out)
	accumulator := NewAccumulator(gearMultiplier.Out)

	for scanner.Scan() {
		line := scanner.Text()
		schema.AddLine(line)
	}

	accumulator.WaitForGearRatios()
	gearMultiplier.WaitForGears()
	partParser.WaitForGears()
	gearFilter.WaitForGears()
	gearParser.FindGears()

	gearParser.WaitForClose()
	gearFilter.WaitForClose()
	partParser.WaitForClose()
	gearMultiplier.WaitForClose()

	fmt.Println("sum:", <-accumulator.Out)

	// sum the gears
}
