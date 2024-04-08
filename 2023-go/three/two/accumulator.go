package two

type Accumulator struct {
	Out chan int
	in  chan int
}

func NewAccumulator(in chan int) *Accumulator {
	return &Accumulator{
		Out: make(chan int),
		in:  in,
	}
}

func (a *Accumulator) WaitForGearRatios() {
	go func() {
		sum := 0

		for ratio := range a.in {
			sum += ratio
		}

		a.Out <- sum
	}()
}
