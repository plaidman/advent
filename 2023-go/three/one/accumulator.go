package one

type Accumulator struct {
	Out   chan int
	in    chan Part
	schem *Schematic
}

func NewAccumulator(schem *Schematic, in chan Part) *Accumulator {
	return &Accumulator{
		Out:   make(chan int),
		in:    in,
		schem: schem,
	}
}

func (a *Accumulator) WaitForParts() {
	go func() {
		result := 0

		for part := range a.in {
			partNum := a.schem.GetPartNumber(part)
			result += partNum
		}

		a.Out <- result
	}()
}
