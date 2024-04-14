package one

func NewMultAccumulator(in chan int) chan int {
	return NewAccumulator(in, multiply, 1)
}

func multiply(item int, accum int) int {
	return item * accum
}
