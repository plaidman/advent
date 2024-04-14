package two

func NewSliceAccumulator[In any](in chan In) chan []In {
	init := make([]In, 0)
	return NewAccumulator(in, gatherSlice, init)
}

func gatherSlice[In any](item In, accum []In) []In {
	return append(accum, item)
}
