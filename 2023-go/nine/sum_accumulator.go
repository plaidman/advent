package nine

func NewSumAccumulator(in chan int) chan int {
	return NewAccumulator(in, sum, 0)
}

func sum(in int, accum int) int {
	return in + accum
}
