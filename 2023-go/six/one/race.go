package one

type Race struct {
	time int
	dist int
}

func NewWinningOptsCounter(in chan Race) chan int {
	return NewPipelineStep(in, countWinningOpts)
}

func countWinningOpts(r Race) int {
	mid := 0
	if r.time%2 == 0 {
		mid = r.time/2
	} else {
		mid = (r.time - 1) / 2
	}

	count := 0
	for ; mid >= 0; mid-- {
		dist := mid * (r.time - mid)

		if dist <= r.dist {
			break
		}

		count++
	}

	total := 0
	if r.time%2 == 0 {
		total = count*2 - 1
	} else {
		total = count * 2
	}

	return total
}
