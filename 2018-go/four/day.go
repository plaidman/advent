package four

type Day struct {
	naps *[]Nap
}

func NewDay() Day {
	naps := make([]Nap, 0)

	return Day{naps: &naps}
}

func (d Day) appendNap(nap Nap) {
	*d.naps = append(*d.naps, nap)
}

func (d Day) asleepAtTime(min int) bool {
	for _, nap := range *d.naps {
		if nap.isAsleepAtMin(min) {
			return true
		}
	}

	return false
}
