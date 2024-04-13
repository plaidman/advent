package one

func NewSliceAccumulator[In any](in chan In) chan []In {
	out := make(chan []In)

	go func() {
		slice := make([]In, 0)

		for item := range in {
			slice = append(slice, item)
		}

		out <- slice
	}()

	return out
}
