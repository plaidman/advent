package one

import "math"

func NewMinAccumulator(in chan int) chan int {
	out := make(chan int)

	go func() {
		curr := math.MaxInt

		for item := range in {
			curr = min(curr, item)
		}

		out <- curr
	}()

	return out
}
