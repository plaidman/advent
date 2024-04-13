package one

import (
	"bufio"
	"fmt"
	"regexp"
	"strconv"
)

func RunPart(scanner *bufio.Scanner) {
	linesChan := make(chan []string)
	productionStepChan := NewProductionStepParser(linesChan)
	allStepsChan := NewSliceAccumulator(productionStepChan)

	scanner.Scan() // seed line
	seedLine := scanner.Text()
	scanner.Scan() // blank line
	scanner.Scan() // label line

	almanacGroup := make([]string, 0)
	for scanner.Scan() {
		line := scanner.Text()

		if line == "" {
			linesChan <- almanacGroup
			almanacGroup = make([]string, 0)
			scanner.Scan() // skip label line
			continue
		}

		almanacGroup = append(almanacGroup, line)
	}
	linesChan <- almanacGroup
	close(linesChan)

	allSteps := <-allStepsChan
	seedChan := make(chan int)
	soilChan := NewPipelineStep(seedChan, allSteps[0].mapNumber)
	fertChan := NewPipelineStep(soilChan, allSteps[1].mapNumber)
	waterChan := NewPipelineStep(fertChan, allSteps[2].mapNumber)
	lightChan := NewPipelineStep(waterChan, allSteps[3].mapNumber)
	tempChan := NewPipelineStep(lightChan, allSteps[4].mapNumber)
	humidChan := NewPipelineStep(tempChan, allSteps[5].mapNumber)
	locChan := NewPipelineStep(humidChan, allSteps[6].mapNumber)
	minChan := NewMinAccumulator(locChan)

	parseSeeds(seedLine, seedChan)
	close(seedChan)

	fmt.Println("min", <-minChan)
}

func parseSeeds(line string, out chan int) {
	pattern := regexp.MustCompile(`(\d+)`)
	matches := pattern.FindAllStringSubmatch(line, -1)

	for _, match := range matches {
		seedNum, _ := strconv.Atoi(match[0])
		out <- seedNum
	}
}
