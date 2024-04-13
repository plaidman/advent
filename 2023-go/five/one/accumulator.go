package one

func Accumulate(in chan int) chan int {
	out := make(chan int)

	go func() {
		sum := 0

		for score := range in {
			sum += score
		}

		out <- sum
	}()

	return out
}
