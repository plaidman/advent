package four

type Nap struct {
	startMin int
	endMin   int
	diff     int
}

func NewNap(startMin int, endMin int) Nap {
	return Nap{startMin: startMin, endMin: endMin, diff: endMin - startMin}
}

func (n Nap) isAsleepAtMin(min int) bool {
	return min >= n.startMin && min < n.endMin
}
