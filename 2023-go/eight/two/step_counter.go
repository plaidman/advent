package two

type StepCounter struct {
	fullMap map[string]Node
	path []int
}

func NewStepCounter(in chan string, fullMap map[string]Node, path []int) chan int {
	sc := StepCounter{
		fullMap: fullMap,
		path: path,
	}

	return NewPipelineStep(in, sc.countSteps)
}

func (sc *StepCounter) countSteps(in string) int {
	pathIndex := 0
	numSteps := 0
	currNode := sc.fullMap[in]

	for {
		dir := sc.path[pathIndex]
		nextLabel := currNode.branches[dir]
		currNode = sc.fullMap[nextLabel]

		numSteps++
		pathIndex = (pathIndex + 1) % len(sc.path)

		if nextLabel[2] == 'Z' {
			break
		}
	}

	return numSteps
}
