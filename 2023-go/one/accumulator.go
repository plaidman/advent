package one

type Accumulator[T any] struct {
	Out chan T
	in chan T
	accFunc func(T, T) T
	init T
}

func NewSumAccumulator(lineIn chan int) *Accumulator[int] {
	accFunc := func(data int, sum int) int {
		return data + sum
	}

	return &Accumulator[int]{
		make(chan int),
		lineIn,
		accFunc,
		0,
	}
}

func (s *Accumulator[T]) WaitForData() {
	go func() {
		acc := s.init

		for i := range s.in {
			acc = s.accFunc(i, acc)
		}

		s.Out <- acc
	}()
}
