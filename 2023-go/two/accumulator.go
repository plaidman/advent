package two

type Accumulator[I any, O any] struct {
	Out chan O
	in chan I
	accFunc func(I, O) O
	init O
}

func NewPartOneAccumulator(lineIn chan Bag) *Accumulator[Bag, int] {
	accFunc := func(data Bag, sum int) int {
		if data.r > 12 || data.g > 13 || data.b > 14 {
			return sum
		}

		return data.id + sum
	}

	return &Accumulator[Bag, int]{
		Out: make(chan int),
		in: lineIn,
		accFunc: accFunc,
		init: 0,
	}
}

func NewPartTwoAccumulator(lineIn chan Bag) *Accumulator[Bag, int] {
	accFunc := func(data Bag, sum int) int {
		return sum + (data.r * data.g * data.b)
	}

	return &Accumulator[Bag, int]{
		Out: make(chan int),
		in: lineIn,
		accFunc: accFunc,
		init: 0,
	}
}

func (s *Accumulator[I, O]) WaitForData() {
	go func() {
		acc := s.init

		for i := range s.in {
			acc = s.accFunc(i, acc)
		}

		s.Out <- acc
	}()
}
