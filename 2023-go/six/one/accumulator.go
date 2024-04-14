package one

func NewAccumulator[In, Out any](
	in chan In,
	accumulate func(In, Out) Out,
	init Out,
) chan Out {
	out := make(chan Out)

	go func() {
		curr := init

		for item := range in {
			curr = accumulate(item, curr)
		}

		out <- curr
	}()

	return out
}
