package two

func NewLCMAccumulator(in chan int) chan int {
	return NewAccumulator(in, lcm, 1)
}

func lcm(num int, accum int) int {
	return num * accum / gcd(num, accum)
}

func gcd(a, b int) int {
	for b != 0 {
		t := b
		b = a % b
		a = t
	}

	return a
}
