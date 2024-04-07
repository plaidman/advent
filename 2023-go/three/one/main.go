package one

import (
	"bufio"
	"fmt"
)

func RunPartOne(scanner *bufio.Scanner) {
	schem := NewSchematic()
	parser := NewParser(schem)
	verifier := NewVerifier(schem, parser.Out)
	accum := NewAccumulator(schem, verifier.Out)

	for scanner.Scan() {
		line := scanner.Text()
		schem.AddLine(line)
	}

	accum.WaitForParts()
	verifier.WaitForParts()
	parser.ParseParts()

	parser.WaitForClose()
	verifier.WaitForClose()

	fmt.Println("result: ", <-accum.Out)
}
