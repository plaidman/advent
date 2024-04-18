package one

import (
	"bufio"
	"fmt"
)

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
	fmt.Println("steps:", traverseMap(fullMap, pathLine))
}

func traverseMap(fullMap map[string]Node, pathLine string) int {
	currNode := fullMap["AAA"]
	numSteps := 0

	for {
		for i := range pathLine {
			dir := pathLine[i]
			var nextNode string

			switch (dir) {
			case 'L':
				nextNode = currNode.branches[0]
			case 'R':
				nextNode = currNode.branches[1]
			}

			numSteps++
			if nextNode == "ZZZ" {
				return numSteps
			}

			if numSteps % 1000000 == 0 {
				fmt.Println("traveling", numSteps)
			}

			currNode = fullMap[nextNode]
		}
	}
}
