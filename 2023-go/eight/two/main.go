package two

import (
	"bufio"
	"fmt"
)

// I needed a hint to realize that the paths were cyclical, so finding the LCM of the path lengths would give the answer.
// I previously had a brute force method using subroutines but it was taking several minutes
func RunPart(scanner *bufio.Scanner) {
	scanner.Scan() // directions
	pathLine := scanner.Text()
	scanner.Scan() // blank line

	lineChan := make(chan string)
	nodeChan := NewNodeParser(lineChan)
	mapChan := NewMapAccumulator(nodeChan)

	for scanner.Scan() {
		line := scanner.Text()
		lineChan <- line
	}
	close(lineChan)

	fullMap := <- mapChan
	path := parsePath(pathLine)

	startNodeChan := make(chan string)
	stepCountChan := NewStepCounter(startNodeChan, fullMap, path)
	lcmChan := NewLCMAccumulator(stepCountChan)

	for name := range fullMap {
		if name[2] == 'A' {
			startNodeChan <- name
		}
	}
	close(startNodeChan)

	fmt.Println(<-lcmChan)
}

func parsePath(pathLine string) []int {
	path := make([]int, 0);

	for _, step := range pathLine {
		if step == 'R' {
			path = append(path, 1)
		} else {
			path = append(path, 0)
		}
	}

	return path
}
