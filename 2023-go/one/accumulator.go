package one

type SumAccumulator struct {
	SumOut chan int
	lineIn chan int
}

func NewSumAccumulator(lineIn chan int) *SumAccumulator {
	return &SumAccumulator{
		make(chan int),
		lineIn,
	}
}

func (s *SumAccumulator) WaitForLines() {
	go func() {
		sum := 0

		for i := range s.lineIn {
			sum += i
		}

		s.SumOut <- sum
	}()
}
