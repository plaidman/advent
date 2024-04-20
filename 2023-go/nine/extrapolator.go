package nine

type Extrapolator struct {
	extrapFunc func([]int) int
}

func NewExtrapolator(in chan []int, part int) chan int {
	e := Extrapolator{}

	if part == 1 {
		e.extrapFuncFactory(extrapNext)
	} else {
		e.extrapFuncFactory(extrapPrev)
	}

	return NewPipelineStep(in, e.extrapFunc)
}

func (e *Extrapolator) extrapFuncFactory(extrapDir func([]int, int) int) {
	e.extrapFunc = func(in []int) int {
		first := in[1] - in[0]
		second := in[2] - in[1]
		third := in[3] - in[2]

		if first == second && second == third {
			return extrapDir(in, first)
		}

		diffs := make([]int, 0, len(in)-1)
		for i := range in {
			if i == len(in)-1 {
				continue
			}

			diffs = append(diffs, in[i+1] - in[i])
		}

		prevDiff := e.extrapFunc(diffs)
		return extrapDir(in, prevDiff)
	}
}

func extrapNext(in []int, diff int) int {
	return in[len(in)-1] + diff
}

func extrapPrev(in []int, diff int) int {
	return in[0] - diff
}
